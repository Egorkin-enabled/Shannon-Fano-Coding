# Shannon-Fano coding

## Intorduction

Console program that allows to create shannon-fano tables for coding characters.

## Description
Program for Shannon-Fano coding calculation.
Made as a result of eduactional process, so not safe.

2024, Kozlov Egor, 2/278, ISUCT.

## Arguments

You can pass filepath as an argument to the program.

```shell
./shannon-fano ./file-to-show.txt 
```

If no file passed, stdin is used.

Use `--help` key to show help menu.

```shell
./shannon-fano --help
```

## Input format

```
<n - count of symbols>
<symbol 1> <probability 1>
...
<symbol n> <probability n>
```

For implementation simplicity and math operation accuracy   probabilities are present as integers.
That means that you have multiply probabilities by 10^x to exclude point part.

For example:

|Symbol|Probability|
|------|-----------|
|a     |0.75       |
|b     |0.05       |
|c     |0.2        |

Must be written as:

```
3
a 75
b  5
c 20
```

Symbols may be written in any order. Program sort them by probability authomatically.

Also, program checks if probabilities are 1 in sum and writes warning if not &mdash; for this method it's not important if probability sum is not 1 but it's main property of probabilities, so it's possible there's mistake in an input.

## Usage

```shell

./shannon-fano --help # To show help

./shannon-fano                    # To read from stdin.
./shannon-fano ./file-to-show.txt # To read from file.

```

## Examples

### example.txt

Input:

```
3
a 75
b  5
c 20

```

Command:

```shell
shannon-fano ./example.txt
```

Output:

```shell
Symbols read: 3
Probability sum: 100
Probability is OK.
┌──────┬──┐
│ .0 a │0 │
│      ├──┼──┐ ← 75/25
│ 10 c │1 │0 │
│      │  ├──┤ ← 20/5
│ 11 b │  │1 │
└──────┴──┴──┘

```

### inputs.txt

Input:

```
32
_ 1450
о  950
е  740
а  640
и  640
т  560
н  560
с  470
р  410
в  390
л  360
к  290
м  260
д  260
п  240
у  210
я  190
ы  160
з  150
ь  150
б  150
г  140
ч  130
й   10
х    9
ж    8
ю    7
ш    6
ц    3
щ    3
э    3
ф    2

```

Command:

```shell
shannon-fano ./inputs.txt
```

Output:

```shell
Symbols read: 32
Probability sum: 9551
WARNING: PROBBILITY SUM IS NOT 1!
Consider to check your inputs.
┌───────────────┬──┬──┬──┐
│ ........000 _ │0 │0 │0 │
│               │  │  ├──┤ ← 1450/950
│ ........001 о │  │  │1 │
│               │  ├──┼──┼──┐ ← 2400/2580
│ .......0100 е │  │1 │0 │0 │
│               │  │  │  ├──┤ ← 740/640
│ .......0101 а │  │  │  │1 │
│               │  │  ├──┼──┤ ← 1380/1200
│ .......0110 и │  │  │1 │0 │
│               │  │  │  ├──┤ ← 640/560
│ .......0111 т │  │  │  │1 │
│               ├──┼──┼──┼──┤ ← 4980/4571
│ .......1000 н │1 │0 │0 │0 │
│               │  │  │  ├──┤ ← 560/470
│ .......1001 с │  │  │  │1 │
│               │  │  ├──┼──┤ ← 1030/1160
│ .......1010 р │  │  │1 │0 │
│               │  │  │  ├──┼──┐ ← 410/750
│ ......10110 в │  │  │  │1 │0 │
│               │  │  │  │  ├──┤ ← 390/360
│ ......10111 л │  │  │  │  │1 │
│               │  ├──┼──┼──┼──┤ ← 2190/2381
│ ......11000 к │  │1 │0 │0 │0 │
│               │  │  │  │  ├──┤ ← 290/260
│ ......11001 м │  │  │  │  │1 │
│               │  │  │  ├──┼──┤ ← 550/710
│ ......11010 д │  │  │  │1 │0 │
│               │  │  │  │  ├──┼──┐ ← 260/450
│ .....110110 п │  │  │  │  │1 │0 │
│               │  │  │  │  │  ├──┤ ← 240/210
│ .....110111 у │  │  │  │  │  │1 │
│               │  │  ├──┼──┼──┼──┤ ← 1260/1121
│ ......11100 я │  │  │1 │0 │0 │  │
│               │  │  │  │  ├──┼──┤ ← 190/310
│ .....111010 ы │  │  │  │  │1 │0 │
│               │  │  │  │  │  ├──┤ ← 160/150
│ .....111011 з │  │  │  │  │  │1 │
│               │  │  │  ├──┼──┼──┤ ← 500/621
│ .....111100 ь │  │  │  │1 │0 │0 │
│               │  │  │  │  │  ├──┤ ← 150/150
│ .....111101 б │  │  │  │  │  │1 │
│               │  │  │  │  ├──┼──┤ ← 300/321
│ .....111110 г │  │  │  │  │1 │0 │
│               │  │  │  │  │  ├──┼──┐ ← 140/181
│ ....1111110 ч │  │  │  │  │  │1 │0 │
│               │  │  │  │  │  │  ├──┼──┬──┐ ← 130/51
│ ..111111100 й │  │  │  │  │  │  │1 │0 │0 │
│               │  │  │  │  │  │  │  │  ├──┼──┐ ← 10/17
│ .1111111010 х │  │  │  │  │  │  │  │  │1 │0 │
│               │  │  │  │  │  │  │  │  │  ├──┤ ← 9/8
│ .1111111011 ж │  │  │  │  │  │  │  │  │  │1 │
│               │  │  │  │  │  │  │  ├──┼──┼──┤ ← 27/24
│ .1111111100 ю │  │  │  │  │  │  │  │1 │0 │0 │
│               │  │  │  │  │  │  │  │  │  ├──┤ ← 7/6
│ .1111111101 ш │  │  │  │  │  │  │  │  │  │1 │
│               │  │  │  │  │  │  │  │  ├──┼──┼──┐ ← 13/11
│ 11111111100 ц │  │  │  │  │  │  │  │  │1 │0 │0 │
│               │  │  │  │  │  │  │  │  │  │  ├──┤ ← 3/3
│ 11111111101 щ │  │  │  │  │  │  │  │  │  │  │1 │
│               │  │  │  │  │  │  │  │  │  ├──┼──┤ ← 6/5
│ 11111111110 э │  │  │  │  │  │  │  │  │  │1 │0 │
│               │  │  │  │  │  │  │  │  │  │  ├──┤ ← 3/2
│ 11111111111 ф │  │  │  │  │  │  │  │  │  │  │1 │
└───────────────┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┘

```