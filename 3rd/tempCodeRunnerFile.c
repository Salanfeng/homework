    char temp_c;
    temp_c=fgetc(sin);
    int pos=0;
    int word_pos=0;
    int flag=1;
    while(temp_c!=EOF){
        if(is_letter(temp_c)){
            flag=0;
            temp_c=to_upper(temp_c);
            word[pos][word_pos]=temp_c;
            word_pos++;
        }
        else{
            if(flag!=1)
                pos++;
            flag=1;
            word_pos=0;
        }
        temp_c=fgetc(sin);
    }