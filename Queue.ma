[top]
components : queue@Queue
in : in done
out : out
Link : in in@queue
Link : out@queue out
Link : done done@queue

[queue]
preparation : 0:0:3:000
capacity :  10
input : enable
output : enable