vector<string> split(string txt, char key = ' '){
    vector<string> ans;
    
    string palTemp = "";
    for(int i = 0; i < txt.size(); i++){
        
        if(txt[i] == key){
            if(palTemp.size() > 0){
                ans.push_back(palTemp);
                palTemp = "";
            }
        } else{
            palTemp += txt[i];
        }
        
    }
    
    if(palTemp.size() > 0)
        ans.push_back(palTemp);
    
    return ans;
}