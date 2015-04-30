#!/usr/bin/python
import argparse, os, sys, subprocess, shutil, copy

def run():
	TOOLCHAIN_PATH = os.getenv("TOOLCHAIN_PATH", "../toolchain")
	TOOLCHAIN_PATH = os.path.realpath(TOOLCHAIN_PATH)

	HFRAMEWORK_PATH = os.getenv("HFRAMEWORK_PATH", "../hFramework")
	HFRAMEWORK_PATH = os.path.realpath(HFRAMEWORK_PATH)

	args = argparse.ArgumentParser()
	args.add_argument("--debug", action="store_true")
	args.add_argument("--release", action="store_true")
	args.add_argument("--hsensors", action="store_true")
	args.add_argument("--pyconnector", action="store_true")
	args = args.parse_args()

	types=["big"]
	versions=["0.9.5", "0.9.6", "0.9.7"]

	rmdir("libs/")
	os.mkdir("libs")

	params = { "TOOLCHAIN_PATH": TOOLCHAIN_PATH, "HFRAMEWORK_PATH": HFRAMEWORK_PATH }

	for type in types:
		for version in versions:
			if args.hsensors:
				if args.debug:
					build(type, version, True, ".", params)
				if args.release:
					build(type, version, False, ".", params)

			if args.pyconnector:
				if args.debug:
					build(type, version, True, "py-connector/", params)
				if args.release:
					build(type, version, False, "py-connector/", params)

def build(type, version, debug, path, params):
	print(type, version, debug)

	params = copy.copy(params)
	params["ROBOCORE_TYPE"] = type
	params["ROBOCORE_VERSION"] = version
	if debug:
		params["DEBUG"] = "1"
	else:
		params["DEBUG"] = "0"

	args = []
	args.append("cmake")
	args.append(path)
	args.append("-Bbuild_tmp")
	args += ["-D{0}={1}".format(k,v) for k, v in params.items()]

	rmdir("build_tmp/")
	subprocess.check_call(args)
	subprocess.check_call(["make", "-Cbuild_tmp/"])

def rmdir(path):
	if os.path.exists(path):
		shutil.rmtree(path)

run()
rmdir("build_tmp/")
