pipeline {
    agent any
    stages {
        stage('Checkout SCM') {
            steps {
                git branch: 'main', url: 'https://github.com/bhoomikashirol/JenkinsDemo.git'
            }
        }
        stage('Clean Build Directory') {
            steps {
                dir('build') {
                    deleteDir()
                }
            }
        }
        stage('Build') {
            steps {
                dir('build') {
                    sh 'cmake ..'
                    sh 'make'
                }
            }
        }
        stage('Add Build Folder to Git') {
            steps {
                script {
                    sh '''
                    cp -r /Documents/build /var/lib/jenkins/workspace/PipelineDemo/build
                    cd /var/lib/jenkins/workspace/PipelineDemo
                    git add build
                    git commit -m "Add build folder"
                    git push origin main
                    '''
                }
            }
        }
        stage('Test') {
            steps {
                dir('build') {
                    sh 'ctest'
                }
            }
        }
    }
}
