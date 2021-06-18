#!/bin/bash
../main -i ../examples/silabas.txt -o temp
if (diff ../examples/silabas.txt temp > dump) 
then
  echo "silabas.txt (CHECK)"
else
  echo "silabas.txt (FAILED)"
fi
../main -r -s -i ../examples/silabas.txt -o dump 2> temp 
if (diff ./expected/silabasCONFLICT.txt temp > dump)
then
  echo "silabasCONFLICT.txt (CHECK)"
else
  echo "silabasCONFLICT.txt (FAILED)"
fi
../main -c -r -i ../examples/silabas.txt 2> temp > dump
if (diff ./expected/silabasCOUNT.txt temp > dump)
then
  echo "silabasCOUNT.txt (CHECK)"
else
  echo "silabasCOUNT.txt (FAILED)"
fi
../main -c -i ../examples/silabas.txt > temp
if (diff ./expected/silabasCOUNT_SIN_ERR.txt temp > dump)
then
  echo "silabasCOUNT_SIN_ERR.txt (CHECK)"
else
  echo "silabasCOUNT_SIN_ERR.txt (FAILED)"
fi
../main -r -i ../examples/silabas.txt -o temp
if (diff ./expected/silabasREV.txt temp > dump)
then
  echo "silabasREV.txt (CHECK)"
else
  echo "silabasREV.txt (FAILED)"
fi


