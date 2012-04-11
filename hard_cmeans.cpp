// Made By: Parth Mudgal

#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

class hcm{
private:
  const int cluster_count;
  const int attribute_count;
  int data_count;
  vector< vector<int> > matrix;
  vector< vector<float> > data;
  vector< vector<float> > center;
  vector< vector<float> > temp_center;

  ostream& out;
public:
  void init_matrix(){
    matrix.resize(cluster_count);
    for(int i=0;i<cluster_count;i++){
      matrix[i].assign(data_count, 0);
    }
    //matrix[0].assign(data_count, 1);
  }

  hcm(int c_count, int a_count, ostream& _o):cluster_count(c_count), 
                                attribute_count(a_count),
                                data_count(5),
                                out(_o)

  {
    init_matrix();
  }

  void read_data(istream& in){

    while(!in.eof()){
      vector<float> row;
      row.resize(attribute_count);
      for(int i=0;i<attribute_count;i++){
        in>>row[i];
      }
      data.push_back(row);
    }
    data_count = data.size();
    init_matrix();
    for(int i=0;i<data_count;i++){
      matrix[i%cluster_count][i]=1;
    }
  }

  void calculate_center(){
    center.clear();
    for(int i=0;i<cluster_count;i++){
      vector<float> acenter;
      acenter.resize(attribute_count);

      for(int j=0;j<attribute_count;j++){
        float sum=0;
        int div=0;
        for(int k=0;k<data_count;k++){
          sum += matrix[i][k]*data[k][j];
          div += matrix[i][k];
        }
        acenter[j] = sum/div;
      }
      center.push_back(acenter);
    }
  }

  void copy_center(){
    temp_center.clear();
    temp_center.resize(center.size());
    for(int i=0;i<center.size();i++){
      temp_center[i].clear();
      temp_center[i].resize(center[i].size());
      for(int j=0;j<center[i].size();j++){
        temp_center[i][j] = center[i][j];
      }
    }
  }

  bool is_equal(vector< vector<float> >& m1, vector< vector<float> >& m2){
    if(m1.size() != m2.size())return false;
    for(int i=0;i<m1.size();i++){
      if(m1[i].size() != m2.size())return false;
      for(int j=0;j<center[i].size();j++){
        if(m1[i][j] != m2[i][j]){
          return false;
        }
      }
    }
    return true;
  }

  void process(){
    temp_center.clear();
    int count=0;
    calculate_center();
    while(!is_equal(center, temp_center) && count<10){
      print_matrix();
      copy_center();

      
      for(int i=0;i<data_count;i++){
        vector<float> distance;
        distance.resize(cluster_count);
        float sum_squared=0;
        float min_sum = 9999;
        int min_index = 0;
        int old_index = 0;
        for(int j=0;j<cluster_count;j++){
          if(matrix[j][i] == 1)old_index = j;
          for(int k=0;k<attribute_count;k++){
            sum_squared += pow((center[j][k] - data[i][k]), 2);
          }
          sum_squared = pow(static_cast<double>(sum_squared), static_cast<double>(0.5));
          if(sum_squared < min_sum){
            min_index = j;
            min_sum = sum_squared;
          }
        }

        matrix[old_index][i] = 0;
        matrix[min_index][i] = 1;

      }

      calculate_center();
      count++;
    }
  }

  template<typename T>
  void print2d(vector<vector<T>> m, ostream& out){
    for(int i=0;i<m.size();i++){
      for(int j=0;j<m[i].size();j++){
        out<<m[i][j]<<" ";
      }
      cout<<endl;
    }
  }

  void print_matrix(){
    int x = cluster_count*4 + cluster_count + 4;
    out<<"|";
    for(int i=0;i<x;i++){
      out<<"-";
    }
    out<<"|";
    out<<endl;

    out<<"|";
    out<<"    |";
    for(int i=0;i<cluster_count;i++){
      out<<" C"<<(i+1)<<" |";
    }
    out<<endl;

    for(int i=0;i<matrix[0].size();i++){
      out<<"| X"<<(i+1)<<" |";
      for(int j=0;j<matrix.size();j++){
        out<<" "<<matrix[j][i]<<"  |";
      }
      out<<endl;
    }


    out<<"|";
    for(int i=0;i<x;i++){
      out<<"-";
    }
    out<<"|";
    out<<endl;

  }

};

int main(int argc, char *argv[])
{
  ofstream out("test2.txt");
  ifstream in("input.txt");
  int data_count, cluster_count;
  in>>data_count;
  in>>cluster_count;
  hcm test(cluster_count, data_count, out);
  test.read_data(in);
  test.process();
  test.print_matrix();
  out.close();
  return 0;
}

