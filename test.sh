#!/bin/bash

rm -f transactions.dat

./build/add_tx transactions.dat "George Washington" 100.00
./build/add_tx transactions.dat "Dan Brown" 120.25
./build/add_tx transactions.dat "Gary Cooper" 229.50
./build/add_tx transactions.dat "Chadwick Hellington" 301.03
./build/add_tx transactions.dat "Sir Chillingham" 10.25
./build/add_tx transactions.dat "Casper the Ghost" 23.23
./build/add_tx transactions.dat "The Sickest of them all" -2.50
./build/add_tx transactions.dat "Basil Fawlty" -1000
./build/add_tx transactions.dat "Harry Potter" 104320.21
./build/add_tx transactions.dat "Alexander Graham Bell" 204.20

./build/print_transactions transactions.dat
