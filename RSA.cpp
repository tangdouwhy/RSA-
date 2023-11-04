#include <bits/stdc++.h>

using namespace std;

#define i64 long long
#define vint vector<int>
#define pfv \
  pair<bool, vint>  // first是正负 second是绝对值 true为非负 , false为负

pfv add(string a, string b);       // 加法
pfv sub(string a, string b);       // 减法
pfv mul(string a, string b);       // 乘法
pfv div(string a, string b);       // 除法
vint sub(vint a, vint b, int id);  // a从i开始的减法
int cmp(vint a, vint b, int i);    // a从i开始的比较
void print(vint a);                // 打印
pfv rem(string a, string b);       // 取余

const int N = 1e7 + 10;

i64 prime[N], cnt;
i64 st[N];

void get_prime() {
  for (int i = 2; i < N; i++) {
    if (!st[i]) prime[cnt++] = i;
    for (int j = 0; prime[j] < N / i; j++) {
      int t = prime[j] * i;
      st[t] = true;
      if (i % prime[j] == 0) {
        break;
      }
    }
  }
}

void print(pfv a) {
  if (a.first == false && a.second.size() && a.second.back() != 0) {
    cout << "-";
  }
  for (int i = a.second.size() - 1; i >= 0; i--) cout << a.second[i];
  cout << endl;
}
// 将字符串转化为倒着的vint
pfv change(string s) {
  bool f = true;
  vint ans;
  if (s[0] == '-') {
    f = false;
    s.erase(s.begin());
  }

  for (i64 i = s.size() - 1; i >= 0; i--) {
    ans.push_back(s[i] - '0');
  }
  return {f, ans};
}

string rechange(pfv a) {
  string ans;
  for (int i = a.second.size() - 1; i >= 0; i--) {
    ans += char(a.second[i] + '0');
  }
  if (a.first == false) {
    ans = "-" + ans;
  }
  if (ans.size())
    return ans;
  else
    return "0";
}

// 比较大小 1:a>b 0:a=b -1:a<b
int cmp(string a, string b) {
  if (a[0] == '-' && b[0] != '-') {
    return -1;
  } else if (a[0] != '-' && b[0] == '-') {
    return 1;
  } else if (a[0] != '-' && b[0] != '-') {
    if (a.size() > b.size()) {
      return 1;
    } else if (a.size() < b.size()) {
      return -1;
    } else {
      if (a > b)
        return 1;
      else if (a == b)
        return 0;
      else
        return -1;
    }
  } else {
    if (a.size() > b.size()) {
      return -1;
    } else if (a.size() < b.size()) {
      return 1;
    } else {
      if (a > b)
        return -1;
      else if (a == b)
        return 0;
      else
        return 1;
    }
  }
}

// 比较大小 1:a>b 0:a=b -1:a<b 从i开始的比较
int cmp(vint a, vint b, int id) {
  if (a.size() && a.begin() + id <= a.end()) a.erase(a.begin(), a.begin() + id);
  while (a.size() && a.back() == 0) a.pop_back();
  while (b.size() && b.back() == 0) b.pop_back();
  if (a.size() != b.size()) {
    if (a.size() > b.size())
      return 1;
    else
      return -1;
  } else {
    for (int i = a.size() - 1; i >= 0; i--) {
      if (a[i] > b[i])
        return 1;
      else if (a[i] < b[i])
        return -1;
    }
    return 0;
  }
}

// 加法
pfv add(string a, string b) {
  pfv x = change(a);
  pfv y = change(b);
  //+ +
  if (x.first && y.first) {
    if (x.second.size() < y.second.size()) return add(b, a);
    vint C;
    int t = 0;
    for (int i = 0; i < x.second.size(); i++) {
      t += x.second[i];
      if (i < y.second.size()) t += y.second[i];
      C.push_back(t % 10);
      t /= 10;
    }

    if (t) C.push_back(t);
    return {true, C};
  } else if (x.first && !y.first) {  //+ -
    b.erase(b.begin());
    return sub(a, b);
  } else if (!x.first && y.first) {  //- +
    a.erase(a.begin());
    return sub(b, a);
  } else {  // - -
    a.erase(a.begin());
    b.erase(b.begin());
    auto c = add(a, b);
    c.first = false;
    return c;
  }
}

// 减法
pfv sub(string a, string b) {
  pfv x = change(a);
  pfv y = change(b);
  if (x.first && y.first) {
    if (cmp(a, b) == 1) {
      for (int i = 0; i < y.second.size(); i++) {
        if (x.second[i] < y.second[i]) {
          x.second[i + 1]--;
          x.second[i] += 10;
        }
        x.second[i] -= y.second[i];
      }
      while (x.second.size() > 1 && x.second.back() == 0) x.second.pop_back();
      return {true, x.second};
    } else if (cmp(a, b) == 0) {
      return {true, vint(1, 0)};
    } else {
      auto c = sub(b, a);
      c.first = false;
      return c;
    }
  } else if (x.first && !y.first) {
    b.erase(b.begin());
    auto c = add(a, b);
    return c;
  } else if (!x.first && y.first) {
    a.erase(a.begin());
    auto c = add(a, b);
    c.first = false;
    return c;
  } else {
    b.erase(b.begin());
    auto c = add(a, b);
    return c;
  }
}

// a从i开始的减法
vint sub(vint a, vint b, int id) {
  for (int i = 0; i < b.size(); i++) {
    if (a[id + i] < b[i]) {
      a[id + i + 1]--;
      a[id + i] += 10;
    }
    a[id + i] -= b[i];
  }

  return a;
}

// 乘法
pfv mul(string a, string b) {
  pfv x = change(a);
  pfv y = change(b);
  bool ansf = (x.first == y.first);
  if (a == "0") return change("0");
  if (b == "0") return change("0");

  vint C;
  C.resize(x.second.size() + y.second.size() + 1);
  for (int i = 0; i < x.second.size(); i++) {
    for (int j = 0; j < y.second.size(); j++) {
      C[i + j] += x.second[i] * y.second[j];
      C[i + j + 1] += C[i + j] / 10;
      C[i + j] %= 10;
    }
  }
  while (C.size() > 1 && C.back() == 0) C.pop_back();
  return {ansf, C};
}

pfv div(string a, string b) {
  if (b == "0") {
    cout << "error" << endl;
    return change(a);
  }
  pfv x = change(a);
  pfv y = change(b);
  bool ansf = (x.first == y.first);
  vint ans(x.second.size(), 0);

  int id = x.second.size() - y.second.size();
  // cout << id << endl;
  // int cnt = 0;
  for (int i = id; i >= 0; i--) {
    while (cmp(x.second, y.second, i) != -1) {
      ans[i]++;
      // cnt++;
      // if (cnt == 10) return {ansf, ans};
      // cout << "id" << ans[id] << endl;
      // cout << "x" << endl;
      // print(x);
      // cout << "y" << endl;
      // print(y);
      x.second = sub(x.second, y.second, i);
    }
  }
  while (ans.size() > 1 && ans.back() == 0) ans.pop_back();
  return {ansf, ans};
}

void test_add() {
  string a = "19173";
  string b = "1937912";
  i64 aa = 19173;
  i64 bb = 1937912;
  print(add(b, a));
  cout << aa + bb << endl;
}
void test_sub() {
  string a = "19173";
  string b = "1937912";
  i64 aa = 19173;
  i64 bb = 1937912;
  print(sub(a, b));
  cout << aa - bb << endl;
}
void test_mul() {
  string a = "19173";
  string b = "1937912";
  i64 aa = 19173;
  i64 bb = 1937912;
  print(mul(a, b));
  cout << aa * bb << endl;
}
void test_div() {
  string a = "19";
  string b = "2";
  i64 aa = 19173;
  i64 bb = 1937912;
  print(div(a, b));
  cout << bb / aa << endl;
}

pfv rem(string a, string b) {
  if (a[0] != '-') {
    return sub(a, rechange(mul(b, rechange(div(a, b)))));
  } else {
    a.erase(a.begin());
    auto x = sub(a, rechange(mul(a, rechange(div(a, b)))));
    x.first = false;
    return add(rechange(x), b);
  }
}

// const string p = "998244353";
// const string q = "1000000007";
const string one = "1";
const string two = "2";
const string zero = "0";

pfv exgcd(pfv a, pfv b, pfv& x, pfv& y) {
  if (zero == rechange(b)) {
    x = change(one);
    y = change(zero);
    return a;
  }
  pfv t = exgcd(b, rem(rechange(a), rechange(b)), x, y);

  auto r = x;

  x = y;

  auto shang = div(rechange(a), rechange(b));

  auto c = mul(rechange(shang), rechange(y));

  y = sub(rechange(r), rechange(c));

  return t;
}

pfv ksm(pfv a, pfv b, pfv m) {
  pfv ans = change("1");
  while (rechange(b) != "0") {
    // print(b);
    if (rem(rechange(b), "2").second.size() &&
        rem(rechange(b), "2").second[0]) {
      ans = mul(rechange(ans), rechange(a));
      ans = rem(rechange(ans), rechange(m));
    }
    a = mul(rechange(a), rechange(a));
    a = rem(rechange(a), rechange(m));
    b = div(rechange(b), "2");
  }
  return ans;
}

pfv ksm(pfv a, pfv b) {
  pfv ans = change("1");
  while (rechange(b) != "0") {
    // print(b);
    if (rem(rechange(b), "2").second.size() &&
        rem(rechange(b), "2").second[0]) {
      ans = mul(rechange(ans), rechange(a));
    }
    a = mul(rechange(a), rechange(a));
    b = div(rechange(b), "2");
  }
  return ans;
}

void testrem() {
  string a = "20967239";
  string b = "2";
  print(div(a, b));
  i64 aa = 20967239;
  i64 bb = 2;
  // print(rem(a, b));
  cout << aa / bb << endl;
}

pfv gcd(pfv a, pfv b) {
  if (rechange(b) == "0") return a;
  return gcd(b, rem(rechange(a), rechange(b)));
}

signed main(void) {
  cin.tie(0)->ios::sync_with_stdio(0);
  get_prime();
  // testrem();
  // return 0;
  string p = rechange(ksm(change(two), change("607")));
  string q = rechange(ksm(change(two), change("521")));
  p = rechange(sub(p, one));
  q = rechange(sub(q, one));
  // p = "998244353";
  // q = "1000000007";

  pfv n = mul(p, q);
  pfv m = mul(rechange(sub(p, one)), rechange(sub(q, one)));

  pfv d, r;
  pfv e;

  for (i64 i = 0; i < cnt; i++) {
    string s = to_string(prime[i]);
    if (rechange(gcd(change(s), m)) == "1") {
      e = change(s);
      break;
    }
  }

  exgcd(e, m, d, r);

  d = rem(rechange(d), rechange(m));
  d = add(rechange(d), rechange(m));
  d = rem(rechange(d), rechange(m));

  string x, y;
  cout << "x = " << endl;
  cin >> x;
  cout << "e = " << endl;
  print(e);
  // print(n);
  y = rechange(ksm(change(x), e, n));

  cout << "y =" << endl << y << endl;

  cout << "d = " << endl;
  print(d);

  cout << "x = " << endl;
  print(ksm(change(y), d, n));
  return (0 ^ 0);
}
