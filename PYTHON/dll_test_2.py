#!/usr/bin/env python

# NOTE: This must be done in a 32 bit version of python!
# @see http://stackoverflow.com/questions/33709391/using-multiple-python-engines-32bit-64bit-and-2-7-3-5

import sys
import os
import ctypes
import pprint


#dll_path = sys.argv[1]
dll_path = "..\\APPLICATIONS\\PROJECT_CODE\\DLLS\\LDLL174__RLOOP__LCCM655\\bin\\Debug"
dll_name = "LDLL174__RLOOP__LCCM655.dll"
dll_filename = os.path.join(dll_path, dll_name)
print "DLL {} exists? {}".format(dll_filename, os.path.exists(dll_filename))
lib = ctypes.CDLL(dll_filename)
print "Lib loaded successfully!"
value = lib.vFCU__Init()
print "Called vFCU__Init()! Got {} in return.".format(value)
try:
    hmm = lib.not_a_real_function()
    print "Called not_a_real_function(), got {} in return.".format(hmm)
except Exception as e:
    print "Called a fake function, got an (expected) exception! ({})".format(e)

    
print "-----"
print "Now let's try a callback..."
# @see http://stackoverflow.com/questions/17980167/writing-python-ctypes-for-function-pointer-callback-function-in-c

#debug_printf_callback = ctypes.WINFUNCTYPE(None, ctypes.POINTER(ctypes.c_byte))  # Returns nothing, takes a byte*

# -------

def errcheck_callback(result, func, arguments):
    if result is not None:  # @todo: should we do this? It seems that errcheck gets called when it is set up, with None as the result...
        print "Python errcheck_callback called: {}, {}, {}".format(result, func.__name__, arguments)
    
# -------


debug_printf_callback = ctypes.CFUNCTYPE(None, ctypes.c_char_p)  # Returns nothing, takes a char*

vDEBUG_PRINTF_WIN32__Set_Callback = lib.vDEBUG_PRINTF_WIN32__Set_Callback
vDEBUG_PRINTF_WIN32__Set_Callback.argtypes = [debug_printf_callback]
vDEBUG_PRINTF_WIN32__Set_Callback.restype = None
vDEBUG_PRINTF_WIN32__Set_Callback.errcheck = errcheck_callback

print "After setting callback -- was errcheck_callback called before this? If so, it's likely called just when setting up the function."

# Define the python function that we'll use for the callback
def debug_printf(val):
    print "Python Debug printf callback called with value '{}'".format(val)
    
# reference the callback to keep it alive
_debug_printf_callback = debug_printf_callback(debug_printf)

# Pass in our referenced python function to the dll function
vDEBUG_PRINTF_WIN32__Set_Callback(_debug_printf_callback)

print "After vDEBUG_PRINTF_WIN32__Set_Callback"

from time import sleep

def fcu_init():
    lib.vFCU__Init()

def fcu_process():
    lib.vFCU__Process()  # @todo: program exits on this call? 

print "Calling vFCU__Init()"
fcu_init()

n = 10
print "Starting vFCU__Process() loop ({})".format(n)
for i in xrange(n):
    print "  Calling vFCU__Process()..."
    #lib.vFCU__Process()
    fcu_process()
    print "  After vFCU__Process() call"
    
print "Done with vFCU__Process() loop!"

# @todo: The program exits during the lib.vFCU__Process() call -- maybe need to initialize temperature or something? 

