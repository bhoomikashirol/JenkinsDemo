pipeline {  
    agent any  

    environment {  
        BUILD_DIR = "/var/lib/jenkins/workspace/PipelineDemo/build"  
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
                    checkout([$class: 'GitSCM', branches: [[name: '*/main'], [name: '*/Test']], userRemoteConfigs: [[url: REPO_URL, credentialsId: GIT_CREDENTIALS_ID]]])  
                    sh 'git checkout main' 
                    sh 'git merge origin/Test' 
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
                    sh 'cppcheck --enable=all --xml --xml-version=2 . 2> cppcheck.xml'  
                }  
                publishCppcheck pattern: 'cppcheck.xml'  
            }  
        }  

        stage('Run Tests') {  
            parallel { 
                stage('Unit Test') {  
                    steps {  
                        script {  
                            sh 'mkdir -p ${BUILD_DIR}/test-results/unit'  
                            dir("${BUILD_DIR}") {  
                                sh './unit_test --gtest_output=xml:${BUILD_DIR}/test-results/unit/test-results.xml'  
                            }  
                            sh 'ls -la ${BUILD_DIR}/test-results/unit'  
                        }  
                        junit '**/test-results/unit/*.xml'  
                    }  
                } 
                stage('Integration Test') {  
                    steps {  
                        script {  
                            sh 'mkdir -p ${BUILD_DIR}/test-results/integration'  
                            dir("${BUILD_DIR}") {  
                                sh './integration_test --gtest_output=xml:${BUILD_DIR}/test-results/integration/test-results.xml'  
                            }  
                            sh 'ls -la ${BUILD_DIR}/test-results/integration'  
                        }  
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
