pipeline {  
    agent any  

    environment {  
        BUILD_DIR = "/var/lib/jenkins/workspace/PipelineDemo/build"  
        TEST_DIR = "/var/lib/jenkins/workspace/PipelineDemo/CRC_UT/test"  
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
                    
                    // Print current branches
                    sh 'git branch -a'
                    
                    // Merge the Test branch into the main branch
                    sh 'git checkout main'
                    sh 'git merge origin/Test'
                    
                    // Print the status after merge
                    sh 'git status'
                }  
            }  
        }  

        stage('Build and Clean') {  
            parallel { 
                stage('Clean Build Directory') { 
                    steps { 
                        script { 
                            sh 'rm -rf ${BUILD_DIR}' 
                            sh 'mkdir -p ${BUILD_DIR}' 
                        } 
                    } 
                } 
                stage('Run CMake and Build') { 
                    steps { 
                        script { 
                            dir("${BUILD_DIR}") { 
                                sh 'pwd'
                                sh 'ls -la /var/lib/jenkins/workspace/PipelineDemo/CRC_UT/test/UT'
                                sh 'ls -la /var/lib/jenkins/workspace/PipelineDemo/CRC_UT/test/IT'
                                sh 'cmake -S .. -B .' 
                                sh 'cmake --build .' 
                            } 
                        } 
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

        stage('Build and Upload Docker Images') { 
            parallel { 
                stage('Build Docker Image') { 
                    steps { 
                        script { 
                            dockerImage = docker.build(registry) 
                        } 
                    } 
                } 
                stage('Upload Docker Image') { 
                    steps { 
                        script { 
                            docker.withRegistry('', registryCredential) { 
                                dockerImage.push() 
                            } 
                        } 
                    } 
                } 
            } 
        } 
    }  
}
