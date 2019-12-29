FROM conanio/gcc9
RUN sudo update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-9 200
RUN pip install gcovr
WORKDIR /app
COPY . .
RUN sudo chown -R conan ./
