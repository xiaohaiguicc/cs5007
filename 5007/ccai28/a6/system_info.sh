# Modified by  chenxi cai 2019-3-15
#!/bin/bash

# server report

report_cores() {
  echo -e "cores: \c"
  cat <<- _EOF_
    $(cat /proc/cpuinfo | awk '/^processor/{print $3}' | wc -l)
_EOF_
}

#report_cores
echo "cores: " $(nproc) 

echo $(free -m | awk 'NR==2{printf "memory: %s MB/%s MB (%.2f%%)\n", $4,$2,$4*100/$2 }')

echo $(df -h | awk '$NF=="/"{printf "primary partition storage: %d/%dGB (%.2f%%)\n", $4,$2,$4*100/$2 }')

