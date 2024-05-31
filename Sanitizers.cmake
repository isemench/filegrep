# File: Sanitizers.cmake

option(ENABLE_ASAN "Enable AddressSanitizer" YES)
option(ENABLE_LSAN "Enable LeakSanitizer" YES)
option(ENABLE_TSAN "Enable ThreadSanitizer" NO)
option(ENABLE_MSAN "Enable MemorySanitizer" NO)
option(ENABLE_UBSAN "Enable UndefinedBehaviorSanitizer" YES)

# if ((ENABLE_ASAN AND (ENABLE_TSAN OR ENABLE_MSAN)) OR
#     (ENABLE_LSAN AND (ENABLE_TSAN OR ENABLE_MSAN)) OR
#     (ENABLE_TSAN AND ENABLE_MSAN)
#      message(FATAL_ERROR "Invalid combination of sanitizers:\n"
#         "ENABLE_ASAN: ${ENABLE_ASAN}\n"
#         "ENABLE_LSAN: ${ENABLE_LSAN}\n"
#         "ENABLE_TSAN: ${ENABLE_TSAN}\n"
#         "ENABLE_MSAN: ${ENABLE_MSAN}\n"
#         "ENABLE_UBSAN: ${ENABLE_UBSAN}\n"
#      )
# )
# endif()

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
