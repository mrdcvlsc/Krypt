# Benchmark

Compiler : g++

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 100 | 14 | 7.14 mb/s | N/A |
| AES128 Dec | ECB | 100 | 9 | 11.11 mb/s | success |
| AES192 Enc | ECB | 100 | 16 | 6.25 mb/s | N/A |
| AES192 Dec | ECB | 100 | 11 | 9.09 mb/s | success |
| AES256 Enc | ECB | 100 | 19 | 5.26 mb/s | N/A |
| AES256 Dec | ECB | 100 | 13 | 7.69 mb/s | success |
| AES128 Enc | CBC | 100 | 14 | 7.14 mb/s | N/A |
| AES128 Dec | CBC | 100 | 10 | 10.00 mb/s | success |
| AES192 Enc | CBC | 100 | 17 | 5.88 mb/s | N/A |
| AES192 Dec | CBC | 100 | 11 | 9.09 mb/s | success |
| AES256 Enc | CBC | 100 | 20 | 5.00 mb/s | N/A |
| AES256 Dec | CBC | 100 | 13 | 7.69 mb/s | success |
| AES128 Enc | CFB | 100 | 14 | 7.14 mb/s | N/A |
| AES128 Dec | CFB | 100 | 14 | 7.14 mb/s | success |
| AES192 Enc | CFB | 100 | 17 | 5.88 mb/s | N/A |
| AES192 Dec | CFB | 100 | 17 | 5.88 mb/s | success |
| AES256 Enc | CFB | 100 | 20 | 5.00 mb/s | N/A |
| AES256 Dec | CFB | 100 | 20 | 5.00 mb/s | success |
