
class MapSquare {
    public:
    MapSquare() {
        is_enemy_path_ = true;
        is_tower_ = true;
        is_free_ = true;
    };
    
    
    private: 
    bool is_enemy_path_;
    bool is_tower_;
    bool is_free_;
};