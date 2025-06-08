#!/bin/bash
g++ main.cpp user.cpp -o main.out

if [ $? -ne 0 ]; then
  echo "❌ 컴파일 실패"
fi

echo "✅ 실행 중..."
./main.out
