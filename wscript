# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

def options(opt):
    opt.load(['compiler_c', 'compiler_cxx'])

def configure(conf):
    conf.load(['compiler_c', 'compiler_cxx'])
    conf.check_cfg(package='libndn-cxx', args=['--cflags', '--libs'], uselib_store='NDN_CXX', mandatory=True)
    conf.check_cfg(package='opendht', args=['--cflags', '--libs'], uselib_store='OPENDHT', mandatory=True)
    conf.check_cfg(package='gnutls', args=['--cflags', '--libs'], uselib_store='GNUTLS', mandatory=True) #三个分开写。。。
    
def build(bld):
    bld.program(
        features ='cxx',
        target='client-test', # 生成的可执行文件名
        source=bld.path.ant_glob(['src/*.cpp', 'src/client/*.cpp']),
        includes = "./src",
        use='NDN_CXX OPENDHT GNUTLS',# 使用的库名
        #use=['NDN_CXX','OPENDHT','GNUTLS'],
    )

    bld.program(
        features='cxx',
        target='server-test',
        source=bld.path.ant_glob(['src/*.cpp','src/server/*.cpp']),
        includes = "./src",
        use='NDN_CXX OPENDHT GNUTLS',
    )
