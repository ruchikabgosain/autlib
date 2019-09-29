extern "C" {
  #include <string.h>
  #include <aut.h>
  #include <aut/write.h>
}

int main(void)
{
  autDescriptor_t *descriptor;
  aut_descriptor_create(&descriptor, 0, 5, 3);

  aut_t *aut;
  aut_create(&aut, descriptor, "t");

  aut_add_transition(aut, 0, 1, "a");
  aut_add_transition(aut, 0, 2, "b");
  aut_add_transition(aut, 2, 2, "f(a)");
  aut_add_transition(aut, 2, 1, "2->1");
  aut_add_transition(aut, 2, 0, "2->0");

  aut_write("aut_write_file.aut", aut);
}


