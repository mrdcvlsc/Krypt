# Benchmark

Compiler : clang++

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 100 | 8 | 12.50 mb/s | N/A |
| AES128 Dec | ECB | 100 | 6 | 16.67 mb/s | success |
| AES192 Enc | ECB | 100 | 9 | 11.11 mb/s | N/A |
| AES192 Dec | ECB | 100 | 7 | 14.29 mb/s | success |
| AES256 Enc | ECB | 100 | 11 | 9.09 mb/s | N/A |
| AES256 Dec | ECB | 100 | 8 | 12.50 mb/s | success |
| AES128 Enc | CBC | 100 | 8 | 12.50 mb/s | N/A |
| AES128 Dec | CBC | 100 | 6 | 16.67 mb/s | success |
| AES192 Enc | CBC | 100 | 10 | 10.00 mb/s | N/A |
| AES192 Dec | CBC | 100 | 7 | 14.29 mb/s | success |
| AES256 Enc | CBC | 100 | 11 | 9.09 mb/s | N/A |
| AES256 Dec | CBC | 100 | 8 | 12.50 mb/s | success |
| AES128 Enc | CFB | 100 | 8 | 12.50 mb/s | N/A |
| AES128 Dec | CFB | 100 | 8 | 12.50 mb/s | success |
| AES192 Enc | CFB | 100 | 10 | 10.00 mb/s | N/A |
| AES192 Dec | CFB | 100 | 10 | 10.00 mb/s | success |
| AES256 Enc | CFB | 100 | 11 | 9.09 mb/s | N/A |
| AES256 Dec | CFB | 100 | 11 | 9.09 mb/s | success |
