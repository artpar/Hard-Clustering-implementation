A Hard Clustering Algorithm Implemented in C++
==

class hcm

Save input data(to be custered) in a file accessible to the program
Input file should contain:
```
firstline : data_column_count <space> clusters_to_be_formed_count
next lines : data rows each with data_column_count values
```

```
22 2
1.807711 1 4.262680 4.488636 87.000000 0.000000 0.000000 0 0 3.891820 0 1 0 0 0 1 1 0 2 2.197225 0.000000 0.000000
3.032810 1 2.772589 2.708050 0.000000 0.000000 0.000000 0 0 4.727388 5 1 0 0 1 1 0 0 9 2.833213 0.000000 0.000000
1.741764 1 2.708050 4.248495 0.000000 0.000000 0.000000 0 0 3.091042 1 1 0 0 0 1 1 0 5 2.564949 0.000000 0.000000
1.774193 1 3.258097 3.784190 0.000000 0.000000 0.000000 0 0 3.258097 0 1 0 0 0 1 0 0 5 2.995732 0.000000 0.000000
1.689824 1 0.000000 0.693147 0.000000 0.000000 0.000000 0 1 1.791759 0 1 1 0 1 0 0 0 4 2.197225 0.000000 0.000000
1.744152 1 5.023881 7.042286 0.000000 0.000000 0.000000 0 0 3.367296 0 1 0 0 0 0 0 0 12 4.499810 0.000000 0.000000
1.939101 1 3.258097 2.995732 75.000000 0.000000 0.000000 0 0 3.433987 0 1 0 0 1 0 0 0 3 2.639057 0.000000 0.000000
```


Output file can be set, output will be generated like this for example


```
|--------------|
|    | C1 | C2 |
| X1 | 1  | 0  |
| X2 | 0  | 1  |
| X3 | 1  | 0  |
| X4 | 0  | 1  |
| X5 | 1  | 0  |
| X6 | 0  | 1  |
| X7 | 1  | 0  |
|--------------|
|--------------|
|    | C1 | C2 |
| X1 | 1  | 0  |
| X2 | 0  | 1  |
| X3 | 0  | 1  |
| X4 | 0  | 1  |
| X5 | 0  | 1  |
| X6 | 0  | 1  |
| X7 | 1  | 0  |
|--------------|
|--------------|
|    | C1 | C2 |
| X1 | 1  | 0  |
| X2 | 0  | 1  |
| X3 | 0  | 1  |
| X4 | 0  | 1  |
| X5 | 0  | 1  |
| X6 | 0  | 1  |
| X7 | 1  | 0  |
|--------------|
|--------------|
|    | C1 | C2 |
| X1 | 1  | 0  |
| X2 | 0  | 1  |
| X3 | 0  | 1  |
| X4 | 0  | 1  |
| X5 | 0  | 1  |
| X6 | 0  | 1  |
| X7 | 1  | 0  |
|--------------|
```



Usage
===

```c
int main(int argc, char *argv[])
{
  ofstream out("test2.txt");
  ifstream in("input.txt");
  int data_count, cluster_count;
  in>>data_attr_count;
  in>>cluster_count;
  hcm test(cluster_count, data_attr_count, out);
  test.read_data(in);
  test.process();
  test.print_matrix();
  out.close();
  return 0;
}```
