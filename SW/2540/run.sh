#!/bin/bash
g++ -std=c++17 main.cpp -o main.out

if [ $? -ne 0 ]; then
  echo "❌ 컴파일 실패"
  exit 1
fi

echo "✅ 실행 중..."
./main.out
