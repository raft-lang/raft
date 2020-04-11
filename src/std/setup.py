from setuptools import setup

setup(
   name='raft_std',
   version='0.1.0',
   description='Standard library for Raft',
   author='Maviek',
   author_email='maviek@maviek.me',
   packages=['raft_std', 'raft_std.thread', 'raft_std.fs', 'raft_std.io'],
   package_dir={'': 'lib'},
)
