struct benchmark {
    template<typename F, typename ...Args>
    static std::chrono::microseconds get_timing(F f, Args&&... args) {
        auto start = std::chrono::high_resolution_clock::now();
        f(std::forward<Args>(args));
        auto stop = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    }

};
