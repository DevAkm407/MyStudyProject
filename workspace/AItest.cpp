#include <stdio.h>
#include<cppflow/cppflow.h>
#include<iostream>
#include<array>
int main() {
  
  auto input = cppflow::decode_jpeg(cppflow::read_file(std::string("workspace/sunflower.png")));
  input = cppflow::cast(input, TF_UINT8, TF_FLOAT);
  input = input / 255.f;
  input = cppflow::expand_dims(input, 0);
  cppflow::model model("tftest");
  auto output = model({{"serving_default_input_1:0", input}},{"StatefulPartitionedCall:0"});

  std::cout << "It's a tiger cat: " << cppflow::arg_max(output, 1) << std::endl;

    return 0;
}
