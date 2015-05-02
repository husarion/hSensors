#!/usr/bin/python
import argparse, os, sys, subprocess, shutil, copy

def log(txt):
	sys.stdout.write(txt + "\n")
	sys.stdout.flush()

def run():
	params = {}

	path = os.getenv("TOOLCHAIN_PATH", "../toolchain")
	params["TOOLCHAIN_PATH"] = os.path.realpath(path)

	path = os.getenv("HFRAMEWORK_PATH", "../hFramework")
	if path is not None:
		params["HFRAMEWORK_PATH"] = os.path.realpath(path)

	path = os.getenv("HPYTHON_PATH", "../hPython")
	if path is not None:
		params["HPYTHON_PATH"] = os.path.realpath(path)

	args = argparse.ArgumentParser()
	args.add_argument("--debug", action="store_true")
	args.add_argument("--release", action="store_true")
	args.add_argument("--main", action="store_true")
	args.add_argument("--pyconnector", action="store_true")
	args.add_argument("--doc", action="store_true")
	args = args.parse_args()

	types=["big"]
	versions=["0.9.5", "0.9.6", "0.9.7"]

	rmdir("libs/")
	os.mkdir("libs")

	for type in types:
		for version in versions:
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
	log("{0} {1} {2}".format(type, version, debug))

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
