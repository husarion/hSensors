#!/usr/bin/python
import argparse
import os
import sys
import subprocess
import shutil
import copy

args = None

def log(txt):
    sys.stdout.write(txt + "\n")
    sys.stdout.flush()


def run():
    global args

    params = {}

    path = os.getenv("TOOLCHAIN_PATH", "../toolchain")
    params["TOOLCHAIN_PATH"] = os.path.realpath(path)

    path = os.getenv("HFRAMEWORK_PATH", "../hFramework")
    if path is not None:
        params["HFRAMEWORK_PATH"] = os.path.realpath(path)

    path = os.getenv("HPYTHON_PATH", "../hPython")
    if path is not None:
        params["HPYTHON_PATH"] = os.path.realpath(path)

    path = os.getenv("HSENSORS_PATH", "../hSensors")
    if path is not None:
        params["HSENSORS_PATH"] = os.path.realpath(path)

    args = argparse.ArgumentParser()
    args.add_argument("--debug", action="store_true")
    args.add_argument("--release", action="store_true")
    args.add_argument("--main", action="store_true")
    args.add_argument("--pyconnector", action="store_true")
    args.add_argument("--doc", action="store_true")
    def_versions = "big:0.9.6,big:0.9.7,big:0.9.8,big:1.0.0"
    args.add_argument("--versions", default=def_versions)
    args.add_argument("--build-revision")
    args.add_argument("--build-revision-from-git", action="store_true")
    args.add_argument("--build-version")
    args = args.parse_args()

    rmdir("libs/")
    os.mkdir("libs")
    rmdir("bin/")
    os.mkdir("bin")

    for info in args.versions.strip().split(","):
        (type, version) = info.split(":")

        if args.main:
            if args.debug:
                build(type, version, True, ".", params)
            if args.release:
                build(type, version, False, ".", params)

        if args.pyconnector and os.path.exists("py-connector/"):
            if args.debug:
                build(type, version, True, "py-connector/", params)
            if args.release:
                build(type, version, False, "py-connector/", params)

    if args.doc:
        os.chdir("doc")
        subprocess.check_call(["./build.sh"])


def build(type, version, debug, path, params):
    global args

    log("{0} {1} {2}".format(type, version, args.debug))

    params = copy.copy(params)
    params["ROBOCORE_TYPE"] = type
    params["ROBOCORE_VERSION"] = version
    if args.build_revision:
        params["BUILD_REVISION"] = args.build_revision
    elif args.build_revision_from_git:
        params["BUILD_REVISION"] = subprocess.check_output('git rev-parse --short HEAD', shell=True).decode('ascii').strip()
    if args.build_version:
        params["BUILD_VERSION"] = args.build_version

    if debug:
        params["DEBUG"] = "1"
    else:
        params["DEBUG"] = "0"

    callargs = []
    callargs.append("cmake")
    callargs.append(path)
    callargs.append("-Bbuild_tmp")
    callargs += ["-D{0}={1}".format(k, v) for k, v in params.items()]

    rmdir("build_tmp/")
    subprocess.check_call(callargs)
    subprocess.check_call(["make", "-Cbuild_tmp/"])


def rmdir(path):
    if os.path.exists(path):
        shutil.rmtree(path)

run()
rmdir("build_tmp/")
