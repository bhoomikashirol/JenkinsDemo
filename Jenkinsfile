pipeline {
    agent any
    stages {
        stage('Clone Repository') {
            steps {
                sh 'git clone -b Code https://github.com/bhoomikashirol/JenkinsDemo.git'
            }
        }
        stage('Clean Build Directory') {
            steps {
                dir('JenkinsDemo/build') {
                    deleteDir()
                }
            }
        }
        stage('Build') {
            steps {
                dir('JenkinsDemo/build') {
                    sh 'cmake ..'
                    sh 'make'
                }
            }
        }
        stage('Run Cppcheck') {
            steps {
                dir('JenkinsDemo') {
                    sh 'cppcheck --xml --xml-version=2 . 2> cppcheck-report.xml'
                }
            }
        }
        stage('Publish Cppcheck Results') {
            steps {
                recordIssues tools: [cppCheck(pattern: 'JenkinsDemo/cppcheck-report.xml')]
            }
        }
    }
    post {
        always {
            cleanWs()
        }
    }
}
