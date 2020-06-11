#include <iostream>
#include <vector>

#define VEC_CAP (1 << 16)
#define ROOT 0
#define BDD_LB_WIDTH 24
#define LB_WIDTH BDD_LB_WIDTH
#define MAX_LB ((1 << LB_WIDTH) - 1)
typedef uint32_t lb_type;
typedef uint32_t tag_off;

struct tag_seg{
    bool sign;
    tag_off begin;
    tag_off end;
};

struct TagNode{
    lb_type left;
    lb_type right;
    lb_type parent;
    tag_seg seg;
    TagNode(lb_type p, tag_off begin, tag_off end){
        parent = p;
        left = 0;
        right = 0;
        seg.sign = false;
        seg.begin = begin;
        seg.end = end;
    }
    unsigned int get_seg_size(){return (seg.end - seg.begin);}
};

class BDDTag{
public:
    std::vector<TagNode> nodes;
    BDDTag();
    ~BDDTag();
    lb_type insert(tag_off pos);
    
private:
    lb_type insert_n_zeros(lb_type cur_lb, size_t num, lb_type last_one_lb);
    lb_type insert_n_ones(lb_type cur_lb, size_t num, lb_type last_one_lb);
    lb_type alloc_node(lb_type parent, tag_off begin, tag_off end);
    
};

// 初始化和析构
BDDTag::BDDTag(){
    nodes.reserve(VEC_CAP);
    nodes.push_back(TagNode(ROOT, 0, 0));
}
BDDTag::~BDDTag(){}

// 插入
lb_type BDDTag::alloc_node(lb_type parent, tag_off begin, tag_off end){
    lb_type lb = nodes.size();
    if(lb < MAX_LB){
        nodes.push_back(TagNode(parent, begin, end));
        return lb;
    }else{
        return ROOT;
    }
}
lb_type BDDTag::insert(tag_off pos){
    lb_type cur_lb = insert_n_zeros(ROOT, pos, ROOT);
    cur_lb = insert_n_ones(cur_lb, 1, ROOT);
    return cur_lb;
}
lb_type BDDTag::insert_n_zeros(lb_type cur_lb, size_t num, lb_type last_one_lb){
    while(num != 0){
        lb_type next = nodes[cur_lb].left;
        size_t next_size = nodes[next].get_seg_size();
        if(next == 0){
            // 没有左子节点，创建。
            tag_off off = nodes[cur_lb].seg.end;
            lb_type new_lb = alloc_node(last_one_lb, off, off + num);
            nodes[cur_lb].left = new_lb;
            cur_lb = new_lb;
            num = 0;
        }else if(next_size > num){
            // 左子节点的段长度比当前剩余0多，拆分。
            tag_off off = nodes[cur_lb].seg.end;
            lb_type new_lb = alloc_node(last_one_lb, off, off + num);
            nodes[cur_lb].left = new_lb;
            cur_lb = new_lb;
            nodes[next].seg.begin = off + num;
            num = 0;
        }else{
            cur_lb = next;
            num -= next_size;
        }
    }
    return cur_lb;
}
lb_type BDDTag::insert_n_ones(lb_type cur_lb, size_t num, lb_type last_one_lb){
    while(num != 0){
        lb_type next = nodes[cur_lb].right;
        tag_off last_end = nodes[cur_lb].seg.end;
        if(next == 0){
            tag_off off = last_end;
            lb_type new_lb = alloc_node(last_one_lb, off, off + num);
            nodes[cur_lb].right = new_lb;
            cur_lb = new_lb;
            num = 0;
        }else{
            tag_off next_end = nodes[next].seg.end;
            size_t next_size = next_end - last_end;
            if(next_size > num){
                tag_off off = last_end;
                lb_type new_lb = alloc_node(last_one_lb, off, off+num);
                nodes[cur_lb].right = new_lb;
                nodes[new_lb].right = next;
                nodes[next].parent = new_lb;
                nodes[next].seg.begin = off + num;
                cur_lb = new_lb;
                num = 0;
            }else{
                cur_lb = next;
                num -= next_size;
            }
        }
    }
    return cur_lb;
}
