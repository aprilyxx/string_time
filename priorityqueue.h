class PriorityTaskQueue {
  public:
    typedef std::deque<Closure*> Queue;
    explicit PriorityTaskQueue(uint32 max_priority = 1, uint32 thread_num = 8)
    : _max_priority(max_priority), _thread_num(thread_num), _cmd_num(0), _stop(false) {
      for(uint32 i = 0; i < _max_priority; ++i){
        _que.push_back(Queue());
      }
    }
    
    ~PriorityTaskQueue(){}
    
    void AddTask(Closure* c, uint32 priority = 0){
      util::ScopedMutex m(&_mutex);
      _que[priority].push_back(c);
      if(_cmd_num++ == 0) _cond.NotifyAll();
    }
    
    void Start(){
      for(uint32 i = 0; i < _thread_num - 1; ++i){
        ::util::NewAutoThread(::NewCallback(this, &PriorityTaskQueue::Loop));
      }
    }
    
    void Stop(){
      _stop = true;
      _cond.NotifyAll();
    }
    
    private:
      util::Mutex _mutex;
      util::CondVariable _cond;
      std::vector<Queue> _que;
      const uint32 _max_priority;
      const uint32 _thread_num;
      uint32 _cmd_num;
      volatile bool _stop;
      void Loop();
      DISALLOW_COPY_AND_ASSIGN(PriorityTaskQueue);
};
