import fs from 'fs'
import frontMatter from "front-matter";

export async function get({ params }) {
    let posts = [];

    for (let file of fs.readdirSync("static/posts")) {
        const query = "static/posts/" + file
        const { body, ...meta } = frontMatter(
            fs.readFileSync(query, "utf8"));

        posts.push({ body, meta, url: file.split(".")[ 0 ] })
    }

    if (!posts) {
        return {
            body: {
                error: new Error("No posts found")
            }
        }
    }

    return {
        body: {
            posts
        }
    }
}