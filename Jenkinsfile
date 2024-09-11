pipeline { 
    agent any 

    environment { 
        BUILD_DIR = "/var/lib/jenkins/workspace/PipelineDemo/build" 
        TEST_DIR = "/var/lib/jenkins/workspace/PipelineDemo/Test/CRC_UT/test" 
        REPO_URL = "https://github.com/bhoomikashirol/JenkinsDemo.git" 
        GIT_CREDENTIALS_ID = 'github-pat' 
        dockerImage = '' 
        registry = 'bhoomika30/helloworld' 
        registryCredential = 'dockerhub_id' 
    } 

    stages { 
        stage('Checkout') { 
            steps { 
                script { 
                    // Checkout the main branch 
                    checkout([$class: 'GitSCM', branches: [[name: '*/main'], [name: '*/Test']], userRemoteConfigs: [[url: REPO_URL, credentialsId: GIT_CREDENTIALS_ID]]]) 
                    
                    // Merge the Test branch into the main branch
                    sh 'git checkout main'
                    sh 'git merge origin/Test'
                } 
            } 
        } 

        stage('Build and Clean') { 
            steps { 
                script { 
                    // Clean the build directory 
                    sh 'rm -rf ${BUILD_DIR}' 
                     
                    // Create the build directory 
                    sh 'mkdir -p ${BUILD_DIR}' 
                     
                    // Run CMake and build 
                    dir("${BUILD_DIR}") {
                        sh 'cmake -S .. -B .' 
                        sh 'cmake --build .' 
                    }
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
            parallel { 
                stage('Unit Test') { 
                    steps { 
                        script { 
                            // Create the test results directory 
                            sh 'mkdir -p ${BUILD_DIR}/test-results/unit' 
                             
                            // Navigate to the build directory and run the unit tests 
                            dir("${BUILD_DIR}") { 
                                sh './unit_test --gtest_output=xml:${BUILD_DIR}/test-results/unit/test-results.xml' 
                            } 
                             
                            // List the contents of the unit test results directory 
                            sh 'ls -la ${BUILD_DIR}/test-results/unit' 
                        } 
                        // Publish JUnit test results 
                        junit '**/test-results/unit/*.xml' 
                    } 
                } 
                stage('Integration Test') { 
                    steps { 
                        script { 
                            // Create the test results directory 
                            sh 'mkdir -p ${BUILD_DIR}/test-results/integration' 
                             
                            // Navigate to the build directory and run the integration tests 
                            dir("${BUILD_DIR}") { 
                                sh './integration_test --gtest_output=xml:${BUILD_DIR}/test-results/integration/test-results.xml' 
                            } 
                             
                            // List the contents of the integration test results directory 
                            sh 'ls -la ${BUILD_DIR}/test-results/integration' 
                        } 
                        // Publish JUnit test results 
                        junit '**/test-results/integration/*.xml' 
                    } 
                } 
            } 
        } 

        stage('Valgrind Analysis') {
            steps {
                script {
                    // Run Valgrind for memory leak analysis
                    sh 'valgrind --leak-check=full --xml=yes --xml-file=valgrind.xml ./unit_test'
                }
                // Publish Valgrind results
                publishValgrind pattern: 'valgrind.xml'
            }
        }

        stage('Build Docker Image'){ 
            steps{ 
                script{ 
                    dockerImage = docker.build registry 
                } 
            } 
        } 

        stage ('Upload image into Dockerhub'){ 
            steps{ 
                script{ 
                    docker.withRegistry( '', registryCredential ) { 
                        dockerImage.push()  
                    } 
                } 
            } 
        } 
    } 
}

