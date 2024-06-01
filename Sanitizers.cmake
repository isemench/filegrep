# File: Sanitizers.cmake

option(ENABLE_ASAN "Enable AddressSanitizer" NO)
option(ENABLE_LSAN "Enable LeakSanitizer" NO)
option(ENABLE_TSAN "Enable ThreadSanitizer" NO)
option(ENABLE_MSAN "Enable MemorySanitizer" NO)
option(ENABLE_UBSAN "Enable UndefinedBehaviorSanitizer" NO)

add_compile_options(
    -fno-omit-frame-pointer
    $<$<BOOL:${ENABLE_ASAN}>:-fsanitize=address>
    $<$<BOOL:${ENABLE_LSAN}>:-fsanitize=leak>
    $<$<BOOL:${ENABLE_TSAN}>:-fsanitize=thread>
    $<$<BOOL:${ENABLE_MSAN}>:-fsanitize=memory>
    $<$<BOOL:${ENABLE_UBSAN}>:-fsanitize=undefined>
)

add_link_options(
    $<$<BOOL:${ENABLE_ASAN}>:-fsanitize=address>
    $<$<BOOL:${ENABLE_LSAN}>:-fsanitize=leak>
    $<$<BOOL:${ENABLE_TSAN}>:-fsanitize=thread>
    $<$<BOOL:${ENABLE_MSAN}>:-fsanitize=memory>
    $<$<BOOL:${ENABLE_UBSAN}>:-fsanitize=undefined>
)
