pipeline {
    agent any

    stages {
        stage('Clone Repository') {
            steps {
                cleanWs()
                sh 'git clone https://github.com/bhoomikashirol/JenkinsDemo.git'
            }
        }

        stage('Build') {
            steps {
                dir('JenkinsDemo') {
                    sh '''
                        mkdir -p build
                        cd build
                        cmake ..
                        make
                    '''
                }
            }
        }

        stage('Test') {
            steps {
                dir('JenkinsDemo/build') {
                    sh './unit_test'
                }
            }
        }

        stage('Run Cppcheck') {
            steps {
                dir('JenkinsDemo') {
                    sh 'cppcheck --enable=all --inconclusive --xml --xml-version=2 . 2> cppcheck_results.xml'
                }
            }
        }

        stage('Publish Cppcheck Results') {
            steps {
                publishCppcheck pattern: 'JenkinsDemo/cppcheck_results.xml'
            }
        }
    }

    post {
        always {
            cleanWs()
        }
    }
}
