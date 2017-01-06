set(PROJECT_GO_LIBS_STD_NAME GO_libraries_std)

file(GLOB GO_DIR_FILES ./*.hpp)
file(GLOB GO_CONFIG_DIR_FILES ./config/*.hpp)
file(GLOB GO_CONFIG_COMPILER_DIR_FILES ./config/compiler/*.hpp)
file(GLOB GO_EXCEPTION_DIR_FILES ./exception/*.hpp)
file(GLOB GO_MVVM_DIR_FILES ./mvvm/*.hpp)
file(GLOB GO_MVVM_UTILITY_DIR_FILES ./mvvm/utility/*.hpp)
file(GLOB GO_PROPERTY_DIR_FILES ./property/*.hpp)
file(GLOB GO_PROPERTY_DETAIL_DIR_FILES ./property/detail/*.hpp)
file(GLOB GO_PROPERTY_NAMELESS_DIR_FILES ./property/nameless/*.hpp)
file(GLOB GO_PROPERTY_NAMELESS_DETAIL_DIR_FILES ./property/nameless/detail/*.hpp)
file(GLOB GO_PROPERTY_POLICY_DIR_FILES ./property/policy/*.hpp)
file(GLOB GO_DIR_SIGNALS_FILES ./signals/*.hpp)
file(GLOB GO_DIR_UTILITY_FILES ./utility/*.hpp)
file(GLOB GO_DIR_UTILITY_ITERATOR_FILES ./utility/iterator/*.hpp)
file(GLOB GO_DIR_UTILITY_STRING_FILES ./utility/string/*.hpp)

add_library(${PROJECT_GO_LIBS_STD_NAME} STATIC
    ${GO_DIR_FILES}
    ${GO_CONFIG_DIR_FILES}
    ${GO_CONFIG_COMPILER_DIR_FILES}
    ${GO_EXCEPTION_DIR_FILES}
    ${GO_MVVM_DIR_FILES}
    ${GO_MVVM_UTILITY_DIR_FILES}
    ${GO_PROPERTY_DIR_FILES}
    ${GO_PROPERTY_DETAIL_DIR_FILES}
    ${GO_PROPERTY_NAMELESS_DIR_FILES}
    ${GO_PROPERTY_NAMELESS_DETAIL_DIR_FILES}
    ${GO_PROPERTY_POLICY_DIR_FILES}
    ${GO_DIR_SIGNALS_FILES}
    ${GO_DIR_UTILITY_FILES}
    ${GO_DIR_UTILITY_ITERATOR_FILES}
	${GO_DIR_UTILITY_STRING_FILES}
)

set_target_properties(${PROJECT_GO_LIBS_STD_NAME} PROPERTIES LINKER_LANGUAGE CXX)

source_group(go FILES ${GO_DIR_FILES})
source_group(go\\config FILES ${GO_CONFIG_DIR_FILES})
source_group(go\\config\\compiler FILES ${GO_CONFIG_COMPILER_DIR_FILES})
source_group(go\\exception FILES ${GO_EXCEPTION_DIR_FILES})
source_group(go\\mvvm FILES ${GO_MVVM_DIR_FILES})
source_group(go\\mvvm\\utility FILES ${GO_MVVM_UTILITY_DIR_FILES})
source_group(go\\property FILES ${GO_PROPERTY_DIR_FILES})
source_group(go\\property\\detail FILES ${GO_PROPERTY_DETAIL_DIR_FILES})
source_group(go\\property\\nameless FILES ${GO_PROPERTY_NAMELESS_DIR_FILES})
source_group(go\\property\\nameless\\detail FILES ${GO_PROPERTY_NAMELESS_DETAIL_DIR_FILES})
source_group(go\\property\\policy FILES ${GO_PROPERTY_POLICY_DIR_FILES})
source_group(go\\signals FILES ${GO_DIR_SIGNALS_FILES})
source_group(go\\utility FILES ${GO_DIR_UTILITY_FILES})
source_group(go\\utility\\iterator FILES ${GO_DIR_UTILITY_ITERATOR_FILES})
source_group(go\\utility\\string FILES ${GO_DIR_UTILITY_STRING_FILES})