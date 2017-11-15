#include <bits/stdc++.h>

using namespace std;

struct Namespace;
struct Function;

struct Function {
	string path;
	int index;
	Namespace *parentNamespace;
	vector<string> call;
	
	Function() {
		index = 0;
	}
} functions[2005];
int functionCnt = 0;

struct Namespace {
	Namespace *parentNamespace;
	map<string, Namespace *> subNamespace;
	map<string, Function *> subFunction;
	
	Namespace() {
		parentNamespace = 0;
	}
} *root;

Function *getFunction(Function *nowFunction, string call) {
	int dotCnt = 0;
	for (char &i: call)
		if (i == '.') {
			i = ' '; ++dotCnt;
		}
	
	Namespace *nowNamespace, *nowRootNamespace = nowFunction->parentNamespace;
	
	string s;
	
	int DotCnt = dotCnt;
	
	for (; nowRootNamespace; nowRootNamespace = nowRootNamespace->parentNamespace) {
		nowFunction = 0;
		nowNamespace = nowRootNamespace;
		
		stringstream Call(call);
		dotCnt = DotCnt;
		
		while (Call >> s) {
			if (!dotCnt) {
				if (!nowNamespace->subFunction.count(s)) break;
				return nowNamespace->subFunction[s];
			}
			else {
				--dotCnt;
				if (!nowNamespace->subNamespace.count(s)) break;
				nowNamespace = nowNamespace->subNamespace[s];
			}
		}
	}
	
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	Namespace *nowNamespace = root = new Namespace();
	Function *nowFunction = 0;
	string fullPath = "";
	
	string s, call;
	while (cin >> s) {
		if (s == "namespace") {
			cin >> s;
			
			if (s.back() == '{')
				s.erase(s.length() - 1);
			
			nowNamespace->subNamespace[s] = new Namespace();
			nowNamespace->subNamespace[s]->parentNamespace = nowNamespace;
			
			fullPath.append(string(".") + s);
			nowNamespace = nowNamespace->subNamespace[s];
		}
		else if (s == "function") {
			cin >> s;
			
			if (s.back() == '{')
				s.erase(s.length() - 1);
			
			nowNamespace->subFunction[s] = nowFunction = &functions[++functionCnt];
			
			fullPath.append(string(".") + s);
			
			nowFunction->parentNamespace = nowNamespace;
			nowFunction->index = functionCnt;
			nowFunction->path = fullPath.substr(1, fullPath.length() - 1);
		}
		else if (s == "{") {
			continue;
		}
		else if (s == "}") {
			while (!fullPath.empty() && fullPath.back() != '.')
				fullPath.erase(fullPath.length() - 1);
			if (!fullPath.empty())
				fullPath.erase(fullPath.length() - 1);
			
			if (nowFunction)
				nowFunction = 0;
			else
				nowNamespace = nowNamespace->parentNamespace;
		}
		else {
			if (s.front() == '{')
				s = s.substr(1, s.length() - 1);
			call = s;
			if (s.back() == '}') {
				s.erase(s.length() - 1);
				call.erase(call.length() - 1);
			}
			while (s.back() != ';') {
				cin >> s;
				call.append(s);
				if (s.back() == '}') {
					s.erase(s.length() - 1);
					call.erase(call.length() - 1);
				}
			}
			if (call.back() == ';')
				call.erase(call.length() - 1);
			nowFunction->call.push_back(call);
		}
	}
	
	for (int i = 1; i <= functionCnt; ++i) {
		cout << "[" << i << "] " << functions[i].path << endl;
		for (string call: functions[i].call) {
			if (nowFunction = getFunction(&functions[i], call)) {
				cout << "  (" << nowFunction->index << ")" << endl;
			}
			else
				cout << "  (ERROR)" << endl;
		}
	}
		
	return 0;
}
