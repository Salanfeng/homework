int f(char *s)
{
  int i = 0, j = 0;
  while (s[j])
    j++;
  for (j--; i < j && s[i] == s[j]; i++, j--)
    ;
  return (i >= j);
}