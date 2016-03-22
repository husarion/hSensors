#!/usr/bin/python
import argparse
import os
import sys
import subprocess
import shutil
import copy

def_versions = "stm32:robocore@1.0.0,core2@0.1.0;linux:rpi@1.0.0"

args = None
params = None

def log(txt):
    sys.stdout.write(txt + "\n")
    sys.stdout.flush()

def run():
    global args, params

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
    args.add_argument("--versions", default=def_versions)
    args.add_argument("--build-revision")
    args.add_argument("--build-revision-from-git", action="store_true")
    args.add_argument("--build-version")
    args = args.parse_args()

    rmdir("libs/")
    os.mkdir("libs")
    rmdir("bin/")
    os.mkdir("bin")

    for tmp in args.versions.strip().split(";"):
        (port, versions) = tmp.split(":")
        for ver in versions.split(","):
            if len(ver) > 0:
                (board, version) = ver.split("@")
                # print(port, board, version)
                process_version(args, port, board, version)
            else:
                process_version(args, port, None, None)
                print(port)
        continue

        (type, version) = info.split(":")

    if args.doc:
        os.chdir("doc")
        subprocess.check_call(["./build.sh"])

def process_version(args, port, board_type, version):

    if args.main:
        if args.debug:
            build(port, board_type, version, True, ".")
        if args.release:
            build(port, board_type, version, False, ".")

    if args.pyconnector and os.path.exists("py-connector/"):
        if args.debug:
            build(type, version, True, "py-connector/")
        if args.release:
            build(type, version, False, "py-connector/")


def build(port, board_type, version, debug, path):
    global args, params

    log("{0} {1} {2}".format(board_type, version, args.debug))

    tmpparams = copy.copy(params)
    tmpparams["PORT"] = port
    if type:
        tmpparams["BOARD_TYPE"] = board_type
    if version:
        tmpparams["BOARD_VERSION"] = version
    if args.build_revision:
        tmpparams["BUILD_REVISION"] = args.build_revision
    elif args.build_revision_from_git:
        tmpparams["BUILD_REVISION"] = subprocess.check_output('git rev-parse --short HEAD', shell=True).decode('ascii').strip()
    if args.build_version:
        tmpparams["BUILD_VERSION"] = args.build_version

    if debug:
        tmpparams["DEBUG"] = "1"
    else:
        tmpparams["DEBUG"] = "0"

    callargs = []
    callargs.append("cmake")
    callargs.append(path)
    callargs.append("-Bbuild_tmp")
    callargs += ["-D{0}={1}".format(k, v) for k, v in tmpparams.items()]
    print(" ".join(callargs))

    rmdir("build_tmp/")
    subprocess.check_call(callargs)
    subprocess.check_call(["make", "-Cbuild_tmp/"])


def rmdir(path):
    if os.path.exists(path):
        shutil.rmtree(path)

run()
rmdir("build_tmp/")
