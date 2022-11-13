#!/bin/sh

echo "ft_container time check : $@"

CC="g++"
CFLAGS="-Wall -Werror -Wextra -std=c++98"
NAMESPACE_="-DTESTING_NAMESPACE="

rm -f ft_time std_time

mkdir -p ./logs/ft
mkdir -p ./logs/std
mkdir -p ./logs/diff

${CC} ${CFLAG} ./tester/time_checker.cpp ${NAMESPACE_}ft -DTYPE=$1 -o ft_time
echo 'type' $1 'for ft_container'
${CC} ${CFLAG} ./tester/time_checker.cpp ${NAMESPACE_}std -DTYPE=$1 -o std_time
echo 'type' $1 'for std_container'
./ft_time 'vector' > './logs/ft/vector'
./ft_time 'stack'  > './logs/ft/stack'
./ft_time 'map'    > './logs/ft/map'
./ft_time 'set'    > './logs/ft/set'


./std_time 'vector' > './logs/std/vector'
./std_time 'stack'  > './logs/std/stack'
./std_time 'map'    > './logs/std/map'
./std_time 'set'    > './logs/std/set'

diff 'logs/ft/vector' 'logs/std/vector' > './logs/diff/vector.diff'
diff 'logs/ft/stack'  'logs/std/stack'  > './logs/diff/stack.diff'
diff 'logs/ft/map'    'logs/std/map'    > './logs/diff/map.diff'
diff 'logs/ft/set'    'logs/std/set'    > './logs/diff/set.diff'
