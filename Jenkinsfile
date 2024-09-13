pipeline {
    agent any

    environment {
        BUILD_DIR = "/var/lib/jenkins/workspace/PipelineDemo/build"
        TEST_DIR = "/var/lib/jenkins/workspace/PipelineDemo/Test"
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

        stage('Setup Test Directory') {
            steps {
                script {
                    sh 'mkdir -p ${TEST_DIR}'
                    sh 'cp -r ${WORKSPACE}/CRC_UT ${TEST_DIR}/'
                    sh 'ls -la ${TEST_DIR}/CRC_UT/test/UT'
                    sh 'ls -la ${TEST_DIR}/CRC_UT/test/IT'
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
                                sh 'cmake -S ${WORKSPACE} -B ${BUILD_DIR}'
                                sh 'cmake --build ${BUILD_DIR}'
                                sh 'ls -la ${BUILD_DIR}'  // Added this line
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
                        junit '**/build/test-results/unit/test-results.xml'
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
                        junit '**/build/test-results/integration/test-results.xml'
                    }
                }
            }
        }

        stage('Valgrind Analysis') {
            parallel {
                stage('Valgrind Unit Test') {
                    steps {
                        script {
                            dir("${BUILD_DIR}") {
                                sh 'valgrind --leak-check=full --xml=yes --xml-file=${BUILD_DIR}/test-results/unit/valgrind.xml ./unit_test'
                                sh 'ls -la ${BUILD_DIR}/test-results/unit'
                            }
                        }
                        publishValgrind pattern: '**/build/test-results/unit/valgrind.xml',
                            failThresholdInvalidReadWrite: '1',
                            failThresholdDefinitelyLost: '1',
                            failThresholdTotal: '1',
                            unstableThresholdInvalidReadWrite: '1',
                            unstableThresholdDefinitelyLost: '1',
                            unstableThresholdTotal: '1',
                            sourceSubstitutionPaths: '',
                            publishResultsForAbortedBuilds: true,
                            publishResultsForFailedBuilds: true,
                            failBuildOnMissingReports: true,
                            failBuildOnInvalidReports: true
                    }
                }
                stage('Valgrind Integration Test') {
                    steps {
                        script {
                            dir("${BUILD_DIR}") {
                                sh 'valgrind --leak-check=full --xml=yes --xml-file=${BUILD_DIR}/test-results/integration/valgrind.xml ./integration_test'
                                sh 'ls -la ${BUILD_DIR}/test-results/integration'
                            }
                        }
                        publishValgrind pattern: '**/build/test-results/integration/valgrind.xml',
                            failThresholdInvalidReadWrite: '1',
                            failThresholdDefinitelyLost: '1',
                            failThresholdTotal: '1',
                            unstableThresholdInvalidReadWrite: '1',
                            unstableThresholdDefinitelyLost: '1',
                            unstableThresholdTotal: '1',
                            sourceSubstitutionPaths: '',
                            publishResultsForAbortedBuilds: true,
                            publishResultsForFailedBuilds: true,
                            failBuildOnMissingReports: true,
                            failBuildOnInvalidReports: true
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
