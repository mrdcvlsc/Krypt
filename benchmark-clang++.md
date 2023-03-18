# Benchmark

Compiler : clang++

## Pure C++

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 200 | 16.52 | 12.11 mb/s | N/A |
| AES128 Dec | ECB | 200 | 12.46 | 16.06 mb/s | success |
| AES192 Enc | ECB | 200 | 19.76 | 10.12 mb/s | N/A |
| AES192 Dec | ECB | 200 | 14.89 | 13.43 mb/s | success |
| AES256 Enc | ECB | 200 | 23.06 | 8.67 mb/s | N/A |
| AES256 Dec | ECB | 200 | 17.33 | 11.54 mb/s | success |
| AES128 Enc | CBC | 200 | 16.91 | 11.83 mb/s | N/A |
| AES128 Dec | CBC | 200 | 12.79 | 15.63 mb/s | success |
| AES192 Enc | CBC | 200 | 20.16 | 9.92 mb/s | N/A |
| AES192 Dec | CBC | 200 | 15.24 | 13.12 mb/s | success |
| AES256 Enc | CBC | 200 | 23.38 | 8.56 mb/s | N/A |
| AES256 Dec | CBC | 200 | 17.67 | 11.32 mb/s | success |
| AES128 Enc | CFB | 200 | 16.94 | 11.81 mb/s | N/A |
| AES128 Dec | CFB | 200 | 16.78 | 11.92 mb/s | success |
| AES192 Enc | CFB | 200 | 20.17 | 9.91 mb/s | N/A |
| AES192 Dec | CFB | 200 | 20.02 | 9.99 mb/s | success |
| AES256 Enc | CFB | 200 | 23.40 | 8.55 mb/s | N/A |
| AES256 Dec | CFB | 200 | 23.25 | 8.60 mb/s | success |

## AES-NI

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 200 | 1.24 | 161.12 mb/s | N/A |
| AES128 Dec | ECB | 200 | 1.29 | 155.14 mb/s | success |
| AES192 Enc | ECB | 200 | 1.34 | 148.90 mb/s | N/A |
| AES192 Dec | ECB | 200 | 1.40 | 142.48 mb/s | success |
| AES256 Enc | ECB | 200 | 1.44 | 139.23 mb/s | N/A |
| AES256 Dec | ECB | 200 | 1.51 | 132.05 mb/s | success |
| AES128 Enc | CBC | 200 | 1.69 | 118.02 mb/s | N/A |
| AES128 Dec | CBC | 200 | 1.69 | 118.26 mb/s | success |
| AES192 Enc | CBC | 200 | 1.79 | 111.71 mb/s | N/A |
| AES192 Dec | CBC | 200 | 1.80 | 110.85 mb/s | success |
| AES256 Enc | CBC | 200 | 1.88 | 106.21 mb/s | N/A |
| AES256 Dec | CBC | 200 | 1.91 | 104.85 mb/s | success |
| AES128 Enc | CFB | 200 | 1.71 | 117.19 mb/s | N/A |
| AES128 Dec | CFB | 200 | 1.58 | 126.42 mb/s | success |
| AES192 Enc | CFB | 200 | 1.81 | 110.66 mb/s | N/A |
| AES192 Dec | CFB | 200 | 1.68 | 119.27 mb/s | success |
| AES256 Enc | CFB | 200 | 1.89 | 105.57 mb/s | N/A |
| AES256 Dec | CFB | 200 | 1.76 | 113.32 mb/s | success |
