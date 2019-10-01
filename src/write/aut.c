#ifdef __cplusplus
extern "C"
{
#endif

#include <aut/write.h>
#include <aut/util/error.h>

#include <inttypes.h>
#include <stdio.h>

autError_t aut_write(const char *path, aut_t *aut)
{
  AUT_CHECK_NULL(path, AUT_EINVAL1);
  AUT_CHECK_NULL(aut,  AUT_EINVAL2);

  FILE *fp;

  if ( (fp = fopen(path, "w+")) == AUT_NULL)
    return AUT_EFOPEN;
  
  autDescriptor_t *descriptor = aut->descriptor;

  fprintf(fp, "des(%" PRIu32 ", %lu, %lu)\n", 
    descriptor->initstate, descriptor->num_transitions, descriptor->num_states);

  for ( size_t i = 0; i < descriptor->num_transitions; ++i) {
    fprintf(fp, "(%" PRIu32 ", \"%s\", %" PRIu32 ")\n", 
      aut->sources[i], aut->actions[i], aut->targets[i]);
  }

  fclose(fp);
}

#ifdef __cplusplus
}
#endif