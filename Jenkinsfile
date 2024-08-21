pipeline { 

    agent any 

  

    environment { 

        BUILD_DIR = "/var/lib/jenkins/workspace/PipelineDemo/build" 

        TEST_DIR = "/var/lib/jenkins/workspace/PipelineDemo/Test/CRC_UT/test/UT" 

        REPO_URL = "https://github.com/bhoomikashirol/JenkinsDemo.git" 

        GIT_CREDENTIALS_ID = 'github-pat'  

    } 

  

    stages { 

        stage('Checkout') { 

            steps { 

                script { 

                    // Checkout the main and Test branches 

                    checkout([$class: 'GitSCM', branches: [[name: '*/main'], [name: '*/Test']], userRemoteConfigs: [[url: REPO_URL, credentialsId: GIT_CREDENTIALS_ID]]]) 

                } 

            } 

        } 

  

        stage('Build') { 

            steps { 

                script { 

                    // Create the build directory 

                    sh 'mkdir -p ${BUILD_DIR}' 

                     

                    // Run CMake and build 

                    sh 'cmake -S . -B ${BUILD_DIR}' 

                    sh 'cmake --build ${BUILD_DIR}' 

                } 

            } 

        } 

  

        stage('Cppcheck') { 

            steps { 

                script { 

                    // Run Cppcheck 

                    sh 'cppcheck --enable=all --xml --xml-version=2 . 2> cppcheck.xml' 

                } 

                // Publish Cppcheck results 

                publishCppcheck pattern: 'cppcheck.xml' 

            } 

        } 

  

        stage('Test') { 

            steps { 

                script { 

                    // Create the test results directory 

                    sh 'mkdir -p ${BUILD_DIR}/test-results' 

                     

                    // Navigate to the build directory and run the tests 

                    dir("${BUILD_DIR}") { 

                        sh './unit_test --gtest_output=xml:${BUILD_DIR}/test-results/test-results.xml' 

                    } 

                     

                    // List the contents of the test results directory 

                    sh 'ls -la ${BUILD_DIR}/test-results' 

                } 

                // Publish JUnit test results 

                junit '**/test-results/*.xml' 

            } 

        } 

    } 

} 

 
