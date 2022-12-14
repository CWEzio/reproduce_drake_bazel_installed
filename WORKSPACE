# -*- mode: python -*-
# vi: set ft=python :

# Copyright (c) 2019, Toyota Research Institute.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
#
# * Neither the name of the copyright holder nor the names of its contributors
#   may be used to endorse or promote products derived from this software
#   without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

workspace(name = "drake_external_examples")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
http_archive(
    name = "rules_python",
    url = "https://github.com/bazelbuild/rules_python/releases/download/0.0.1/rules_python-0.0.1.tar.gz",
    sha256 = "aa96a691d3a8177f3215b14b0edc9641787abaaa30363a080165d06ab65e1161",
)
load("@rules_python//python:repositories.bzl", "py_repositories")
py_repositories()

# Choose which nightly build of Drake to use.
DRAKE_RELEASE = "latest"  # Can also use YYYYMMDD here, e.g., "20191026".
DRAKE_CHECKSUM = ""       # When using YYYYMMDD, best to add a checksum here.
OS_CODENAME = "focal"     # Permitted values are "focal" or "mac".

# To use a local unpacked Drake binary release instead of an http download, set
# this variable to the correct path, e.g., "/opt/drake".
# INSTALLED_DRAKE_DIR = None
INSTALLED_DRAKE_DIR = "/opt/drake" 


# This is only relevant when INSTALLED_DRAKE_DIR is set.
new_local_repository(
    name = "drake_artifacts",
    path = INSTALLED_DRAKE_DIR,
    build_file_content = "#",
) if INSTALLED_DRAKE_DIR else None

# This is only relevant when INSTALLED_DRAKE_DIR is unset.
http_archive(
    name = "drake_artifacts",
    url = "https://drake-packages.csail.mit.edu/drake/nightly/drake-{}-{}.tar.gz".format(DRAKE_RELEASE, OS_CODENAME),
    sha256 = DRAKE_CHECKSUM,
    strip_prefix = "drake/",
    build_file_content = "#",
) if not INSTALLED_DRAKE_DIR else None

# Load and run the repository rule that knows how to provide the @drake
# repository based on a Drake binary release.
load("@drake_artifacts//:share/drake/repo.bzl", "drake_repository")

drake_repository(name = "drake")
