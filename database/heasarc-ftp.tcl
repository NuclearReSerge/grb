#!/usr/bin/expect

if { $argc < 1 } {
  exit 1
}

set FTP_SERVER "heasarc.gsfc.nasa.gov"
set FTP_USERNAME "anonymous"
set FTP_PASSWORD ""
set DIR "heasarc/dbase/dump"
set GUNZIP ".gz"


spawn ftp $FTP_SERVER
expect "Name"
send "$FTP_USERNAME\r"
expect "Password:"
send "FTP_PASSWORD\r"
expect "ftp>"
send "cd $DIR\r"
expect "ftp>"
send "bin\r"


foreach FILE $argv {
  set REMOTE_FILE $FILE$GUNZIP
  send "get $REMOTE_FILE\r"
  expect {
    "Transfer complete" {
      puts "OK"
    }
    "No such file or directory" {
      send "bye\r"
      puts "FILE = $REMOTE_FILE not found"
      exit 2
    }
  }
}

send "bye\r"
expect "Goodbye."
exit 0