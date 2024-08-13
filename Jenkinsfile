pipeline {
    agent any

    stages {
        stage('Clean Build Directory') {
            steps {
                script {
                    dir('build') {
                        sh 'rm -rf *'
                    }
                }
            }
        }
        stage('Checkout') {
            steps {
                git url: 'https://github.com/your-repo/PipelineDemo.git', branch: 'main'
            }
        }
        stage('Build') {
            steps {
                script {
                    dir('build') {
                        sh 'cmake ..'
                        sh 'make'
                    }
                }
            }
        }
        stage('Test') {
            steps {
                script {
                    dir('build') {
                        sh './unit_test'
                    }
                }
            }
        }
    }
    post {
        always {
            cleanWs()
        }
    }
}
