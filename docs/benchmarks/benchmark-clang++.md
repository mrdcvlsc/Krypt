# Benchmark

Compiler : clang++

## Pure C++

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 128 | 14.11 | 9.07 mb/s | N/A |
| AES128 Dec | ECB | 128 | 15.10 | 8.48 mb/s | success |
| AES192 Enc | ECB | 128 | 16.93 | 7.56 mb/s | N/A |
| AES192 Dec | ECB | 128 | 18.17 | 7.04 mb/s | success |
| AES256 Enc | ECB | 128 | 19.75 | 6.48 mb/s | N/A |
| AES256 Dec | ECB | 128 | 21.25 | 6.02 mb/s | success |
| AES128 Enc | CBC | 128 | 14.15 | 9.05 mb/s | N/A |
| AES128 Dec | CBC | 128 | 15.33 | 8.35 mb/s | success |
| AES192 Enc | CBC | 128 | 16.98 | 7.54 mb/s | N/A |
| AES192 Dec | CBC | 128 | 18.40 | 6.96 mb/s | success |
| AES256 Enc | CBC | 128 | 19.80 | 6.47 mb/s | N/A |
| AES256 Dec | CBC | 128 | 21.47 | 5.96 mb/s | success |
| AES128 Enc | CFB | 128 | 14.31 | 8.94 mb/s | N/A |
| AES128 Dec | CFB | 128 | 14.23 | 9.00 mb/s | success |
| AES192 Enc | CFB | 128 | 17.14 | 7.47 mb/s | N/A |
| AES192 Dec | CFB | 128 | 17.06 | 7.50 mb/s | success |
| AES256 Enc | CFB | 128 | 19.96 | 6.41 mb/s | N/A |
| AES256 Dec | CFB | 128 | 19.88 | 6.44 mb/s | success |

## AES-NI

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 128 | 0.86 | 149.23 mb/s | N/A |
| AES128 Dec | ECB | 128 | 0.77 | 165.77 mb/s | success |
| AES192 Enc | ECB | 128 | 0.93 | 137.97 mb/s | N/A |
| AES192 Dec | ECB | 128 | 0.84 | 153.09 mb/s | success |
| AES256 Enc | ECB | 128 | 0.93 | 137.12 mb/s | N/A |
| AES256 Dec | ECB | 128 | 0.89 | 143.05 mb/s | success |
| AES128 Enc | CBC | 128 | 0.89 | 143.99 mb/s | N/A |
| AES128 Dec | CBC | 128 | 1.03 | 123.96 mb/s | success |
| AES192 Enc | CBC | 128 | 0.96 | 133.97 mb/s | N/A |
| AES192 Dec | CBC | 128 | 1.09 | 117.06 mb/s | success |
| AES256 Enc | CBC | 128 | 1.01 | 127.33 mb/s | N/A |
| AES256 Dec | CBC | 128 | 1.16 | 110.52 mb/s | success |
| AES128 Enc | CFB | 128 | 1.09 | 117.83 mb/s | N/A |
| AES128 Dec | CFB | 128 | 0.99 | 129.74 mb/s | success |
| AES192 Enc | CFB | 128 | 1.15 | 111.26 mb/s | N/A |
| AES192 Dec | CFB | 128 | 1.05 | 121.81 mb/s | success |
| AES256 Enc | CFB | 128 | 1.20 | 106.23 mb/s | N/A |
| AES256 Dec | CFB | 128 | 1.09 | 116.93 mb/s | success |
