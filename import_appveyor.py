"""
This script uses the AppVeyor API to check if the current build
has succeeded and download all produced artifacts.
"""

import os
import os.path as pt
import sys
import json
import urllib.request
from http.client import HTTPSConnection
import time


APPVEYOR_URL = 'ci.appveyor.com'


def appveyor_api(*request, content_type_json=True, **kwargs):
    conn = HTTPSConnection(APPVEYOR_URL)
    headers = {'Authorization': 'Bearer ' + os.environ['APPVEYOR_TOKEN']}
    if content_type_json:
        headers['Content-Type'] = 'application/json'
    url = '/'.join(['/api', *request])
    if kwargs:
        url += '?' + '&'.join('%s=%s' % (k, v) for k, v in kwargs.items() if v is not None)
    conn.request('GET', url, headers=headers)
    response = conn.getresponse()
    data = response.read()
    content_type = response.getheader('Content-type', '').lower().split(';')
    content_type = [s.strip() for s in content_type]
    charset = [s for s in content_type if 'charset' in s]
    if charset:
        encoding = charset[-1].partition('=')[2].strip()
    else:
        encoding = 'utf-8'
    data = data.decode(encoding)
    if 'application/json' in content_type:
        data = json.loads(data)
    if response.status != 200:
        raise RuntimeError('HTTP response %s: "%s"' % (response.status, data))
    return data


def project_history(
        records_per_page=10,
        start_build_id=None,
        branch=None,
        accountname=None,
        projectslug=None
):
    return appveyor_api(
        'projects',
        accountname or os.environ['APPVEYOR_ACCOUNTNAME'],
        projectslug or os.environ['APPVEYOR_PROJECTSLUG'],
        'history',
        recordsNumber=records_per_page,
        startBuildId=start_build_id,
        branch=branch,
    )


def get_build_for_commit(commit=None, accountname=None, projectslug=None):
    commit = commit or os.environ['CI_COMMIT_SHA']
    start_build_id = None
    build = None
    while not build:
        history = project_history(
            start_build_id=start_build_id,
            accountname=accountname,
            projectslug=projectslug,
        )
        if not len(history['builds']) or \
                (len(history['builds']) == 1
                 and history['builds'][-1]['commitId'] != commit):
            raise RuntimeError('commit %s not found', commit)
        start_build_id = history['builds'][-1]['buildId']
        build = [b for b in history['builds'] if b['commitId'] == commit]
    return build[0]


def get_build_by_version(version, accountname=None, projectslug=None):
    return appveyor_api(
        'projects',
        accountname or os.environ['APPVEYOR_ACCOUNTNAME'],
        projectslug or os.environ['APPVEYOR_PROJECTSLUG'],
        'build',
        version,
    )


def get_job_artifacts(jobid):
    return appveyor_api('buildjobs', jobid, 'artifacts')


def download_artifacts(jobids, outdir='.'):
    for jobid in jobids:
        artifacts = get_job_artifacts(jobid)
        print('downloading artifacts for job', jobid)
        for artifact in artifacts:
            print('downloading', artifact['fileName'])
            url = '/'.join(['https:/', APPVEYOR_URL, 'api', 'buildjobs',
                            jobid, 'artifacts', artifact['fileName']])
            destination = pt.join(outdir,  artifact['fileName'])
            os.makedirs(pt.dirname(destination), exist_ok=True)
            urllib.request.urlretrieve(url, destination)


def main():
    build = get_build_for_commit()
    while True:
        details = get_build_by_version(build['version'])
        status = [j['status'].lower() for j in details['build']['jobs']]
        failed = 'failed' in status or 'cancelled' in status
        success = all(s == 'success' for s in status)
        if failed:
            print('External job failed.', file=sys.stderr)
            sys.exit(1)
        if success:
            break
        else:
            print('Waiting for external job to finish...')
            time.sleep(30)
    jobids = [j['jobId'] for j in details['build']['jobs']]
    download_artifacts(jobids)
    pass


if __name__ == '__main__':
    main()
