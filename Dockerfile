# Use CentOS 8 as the base image
FROM quay.io/centos/centos:stream9

RUN yum upgrade -y && \
    yum install -y gcc g++ cmake bash diffutils gdb 

# Set working directory to /app (you can change this to anything you like)
WORKDIR /app

# Expose port 80 for web servers, or whatever port your application uses
EXPOSE 80

# Run commands when the container is created
CMD ["bash"]