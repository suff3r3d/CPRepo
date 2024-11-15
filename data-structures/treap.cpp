//replace sum with many other function, just like cnt
struct item {
    long long prior, value, cnt, sum;
    bool rev;
    item *l, *r;
    item(long long value): prior(rand()), value(value), cnt(1), rev(false), sum(value), l(0), r(0) {}
};

long long cnt (item* it) {
    return it ? it->cnt : 0;
}

long long sum (item* it) {
    return it ? it->sum : 0;
}

void upd_cnt (item* it) {
    if (it)
        it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

void upd_sum(item* it) {
    if (it) 
        it->sum = sum(it->l) + sum(it->r) + it->value;
}

void push (item* it) {
    if (it && it->rev) {
        it->rev = false;
        swap(it->l, it->r);
        if (it->l)  it->l->rev ^= true;
        if (it->r)  it->r->rev ^= true;
    }
}

void merge (item* & t, item* l, item* r) {
    push (l);
    push (r);
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge (l->r, l->r, r),  t = l;
    else
        merge (r->l, l, r->l),  t = r;
    upd_cnt(t);
    upd_sum(t);
}

// split so that the number of the node in the left is "num"
void split (item* t, item* & l, item* & r, long long num, long long add = 0) {
    if (!t)
        return void( l = r = 0 );
    push (t);
    int cur_num = add + cnt(t->l);
    if (num <= cur_num)
        split (t->l, l, t->l, num, add),  r = t;
    else
        split (t->r, t->r, r, num, add + 1 + cnt(t->l)),  l = t;

    upd_cnt(t);
    upd_sum(t);
}

// l, r are 1-indexed
void reverse (item* t, int l, int r) {
    item *t1, *t2, *t3;
    split (t, t1, t2, l-1);
    split (t2, t2, t3, r-l+1);
    t2->rev ^= true;
    merge (t, t1, t2);
    merge (t, t, t3);
}

void traverse (item* t) {
    if (!t)  return;
    push (t);
    traverse (t->l);
    // do stuff with current value
    cout << t->value << " ";
    traverse (t->r);
}