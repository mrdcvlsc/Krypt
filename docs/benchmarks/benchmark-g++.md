# Benchmark

Compiler : g++

## Pure C++

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 200 | 28.33 | 7.06 mb/s | N/A |
| AES128 Dec | ECB | 200 | 20.86 | 9.59 mb/s | success |
| AES192 Enc | ECB | 200 | 33.94 | 5.89 mb/s | N/A |
| AES192 Dec | ECB | 200 | 24.90 | 8.03 mb/s | success |
| AES256 Enc | ECB | 200 | 39.59 | 5.05 mb/s | N/A |
| AES256 Dec | ECB | 200 | 28.93 | 6.91 mb/s | success |
| AES128 Enc | CBC | 200 | 28.51 | 7.01 mb/s | N/A |
| AES128 Dec | CBC | 200 | 21.14 | 9.46 mb/s | success |
| AES192 Enc | CBC | 200 | 34.16 | 5.85 mb/s | N/A |
| AES192 Dec | CBC | 200 | 25.64 | 7.80 mb/s | success |
| AES256 Enc | CBC | 200 | 40.29 | 4.96 mb/s | N/A |
| AES256 Dec | CBC | 200 | 29.47 | 6.79 mb/s | success |
| AES128 Enc | CFB | 200 | 28.66 | 6.98 mb/s | N/A |
| AES128 Dec | CFB | 200 | 28.89 | 6.92 mb/s | success |
| AES192 Enc | CFB | 200 | 34.50 | 5.80 mb/s | N/A |
| AES192 Dec | CFB | 200 | 34.43 | 5.81 mb/s | success |
| AES256 Enc | CFB | 200 | 40.31 | 4.96 mb/s | N/A |
| AES256 Dec | CFB | 200 | 40.06 | 4.99 mb/s | success |

## AES-NI

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 200 | 1.44 | 138.91 mb/s | N/A |
| AES128 Dec | ECB | 200 | 1.29 | 155.34 mb/s | success |
| AES192 Enc | ECB | 200 | 1.54 | 129.78 mb/s | N/A |
| AES192 Dec | ECB | 200 | 1.39 | 144.09 mb/s | success |
| AES256 Enc | ECB | 200 | 1.74 | 114.76 mb/s | N/A |
| AES256 Dec | ECB | 200 | 1.45 | 137.50 mb/s | success |
| AES128 Enc | CBC | 200 | 1.58 | 126.62 mb/s | N/A |
| AES128 Dec | CBC | 200 | 1.53 | 130.92 mb/s | success |
| AES192 Enc | CBC | 200 | 1.68 | 119.14 mb/s | N/A |
| AES192 Dec | CBC | 200 | 1.69 | 118.48 mb/s | success |
| AES256 Enc | CBC | 200 | 1.80 | 110.98 mb/s | N/A |
| AES256 Dec | CBC | 200 | 1.79 | 111.73 mb/s | success |
| AES128 Enc | CFB | 200 | 1.78 | 112.62 mb/s | N/A |
| AES128 Dec | CFB | 200 | 1.64 | 122.26 mb/s | success |
| AES192 Enc | CFB | 200 | 1.88 | 106.33 mb/s | N/A |
| AES192 Dec | CFB | 200 | 1.76 | 113.45 mb/s | success |
| AES256 Enc | CFB | 200 | 2.01 | 99.43 mb/s | N/A |
| AES256 Dec | CFB | 200 | 1.92 | 104.33 mb/s | success |
