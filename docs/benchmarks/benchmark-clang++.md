# Benchmark

Compiler : clang++

## Pure C++

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 512 | 42.99 | 11.91 mb/s | N/A |
| AES128 Dec | ECB | 512 | 32.23 | 15.88 mb/s | success |
| AES192 Enc | ECB | 512 | 51.36 | 9.97 mb/s | N/A |
| AES192 Dec | ECB | 512 | 38.52 | 13.29 mb/s | success |
| AES256 Enc | ECB | 512 | 60.01 | 8.53 mb/s | N/A |
| AES256 Dec | ECB | 512 | 45.01 | 11.38 mb/s | success |
| AES128 Enc | CBC | 512 | 43.56 | 11.75 mb/s | N/A |
| AES128 Dec | CBC | 512 | 33.25 | 15.40 mb/s | success |
| AES192 Enc | CBC | 512 | 51.60 | 9.92 mb/s | N/A |
| AES192 Dec | CBC | 512 | 39.46 | 12.97 mb/s | success |
| AES256 Enc | CBC | 512 | 60.77 | 8.43 mb/s | N/A |
| AES256 Dec | CBC | 512 | 45.93 | 11.15 mb/s | success |
| AES128 Enc | CFB | 512 | 43.86 | 11.67 mb/s | N/A |
| AES128 Dec | CFB | 512 | 43.48 | 11.77 mb/s | success |
| AES192 Enc | CFB | 512 | 52.20 | 9.81 mb/s | N/A |
| AES192 Dec | CFB | 512 | 51.88 | 9.87 mb/s | success |
| AES256 Enc | CFB | 512 | 60.78 | 8.42 mb/s | N/A |
| AES256 Dec | CFB | 512 | 60.50 | 8.46 mb/s | success |

## AES-NI

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 512 | 3.44 | 148.73 mb/s | N/A |
| AES128 Dec | ECB | 512 | 3.08 | 165.99 mb/s | success |
| AES192 Enc | ECB | 512 | 3.73 | 137.23 mb/s | N/A |
| AES192 Dec | ECB | 512 | 3.34 | 153.47 mb/s | success |
| AES256 Enc | ECB | 512 | 3.77 | 135.82 mb/s | N/A |
| AES256 Dec | ECB | 512 | 3.62 | 141.59 mb/s | success |
| AES128 Enc | CBC | 512 | 3.56 | 143.95 mb/s | N/A |
| AES128 Dec | CBC | 512 | 4.13 | 123.92 mb/s | success |
| AES192 Enc | CBC | 512 | 3.83 | 133.52 mb/s | N/A |
| AES192 Dec | CBC | 512 | 4.40 | 116.26 mb/s | success |
| AES256 Enc | CBC | 512 | 4.07 | 125.84 mb/s | N/A |
| AES256 Dec | CBC | 512 | 4.67 | 109.69 mb/s | success |
| AES128 Enc | CFB | 512 | 4.34 | 118.04 mb/s | N/A |
| AES128 Dec | CFB | 512 | 3.95 | 129.68 mb/s | success |
| AES192 Enc | CFB | 512 | 4.61 | 111.09 mb/s | N/A |
| AES192 Dec | CFB | 512 | 4.25 | 120.49 mb/s | success |
| AES256 Enc | CFB | 512 | 4.86 | 105.44 mb/s | N/A |
| AES256 Dec | CFB | 512 | 4.41 | 116.06 mb/s | success |
