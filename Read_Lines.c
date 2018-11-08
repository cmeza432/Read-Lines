/*
 *Function      : read_lines
 *Description   : Takes file input and returns 2d array and length of file
 *Parameter     : Array where file will be stored and int to store length
 *returns       : Success or Fail
*/
int read_lines(char*** dest, int* num_lines)
{
  char buffer[2048];
  char** temp_arr;
  char* temp_line;
  
  *num_lines = 0;
  
  /* Try opening the file */
  FILE* fp = fopen("input.txt", "r");
  if (fp == NULL)
  {
    printf("Error opening file for reading. Exiting.\n");
    return 0;
  }
 
  /* Read the file line by line into the buffer */
  while (fgets(buffer, sizeof(buffer), fp) != NULL)
  {
    int line_length = strlen(buffer);
    char* s;

    /* Check if it's a blank line and skip if it is */
    if (strcmp(buffer, "\r\n") == 0 || strcmp(buffer, "\n") == 0 || strcmp(buffer, "\n\r") == 0)
      continue;
    
    (*num_lines)++;
    
    /* Allocate or reallocate enough space for a pointer to each line we've come across thus far. */
    if (*dest == NULL)
    {
      temp_arr = malloc(*num_lines * sizeof(char*));
    }
    else
    {
      temp_arr = realloc(*dest, *num_lines * sizeof(char*));
    }
    
    if (!temp_arr)
    {
      printf("Error (re)allocating memory. Exiting.\n");
      return 0;
    }
    *dest = temp_arr;
    
    /* Allocate enough space for the current line. */
    temp_line = malloc(line_length * sizeof(char));
    if (!temp_line)
    {
      printf("Error allocating space for the line. Skipping the line.\n");
      (*num_lines)--;
      continue;
    }
    (*dest)[*num_lines-1] = temp_line;
    
    /* Copy the current line into the array */
    strcpy((*dest)[*num_lines-1], buffer);
    
    /* Get rid of that pesky newline for both Mac and Windows */
    s = (*dest)[*num_lines-1];
    if (s[line_length - 2] == '\r' || s[line_length - 2] == '\n')
      s[line_length - 2] = '\0';
    else if (s[line_length - 1] == '\n')
      s[line_length - 1] = '\0';
  }
  
  fclose(fp);
  
  return 1;
}