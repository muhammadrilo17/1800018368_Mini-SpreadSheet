using namespace std;
class SpreadSheet{
	private:
		bool found;
		int i;
		int indexcode;
		
	public:
		string findinstructions(string Action){
			found = false;
			for(i=0;(i<6 && !found);i++){
				if(Action.at(i)=='('){
					indexcode = i;
					found = true;
				}
			}
			Action = Action.substr(0,indexcode-1);
			for(int i=0;i<Action.length();i++){
				Action.at(i) = tolower(Action.at(i));
			}	
			return Action;
		}
};
